#include <iostream>
#include <iomanip>
#include <thread>
#include <vector>
#include <random>
#include <future>


template<typename Iter>
Iter find_min(Iter first, Iter last) {
    Iter min = first;
    if (first == last)
        return first;
    do {
        ++first;
        if (*min > *first) {
            min = first;
        }
       
    } while (first != last);
    return min;
}

void choice_sort(std::vector<int> vect, std::promise<std::vector<int>> promis) {
    int countCore = std::thread::hardware_concurrency() - 2;
    int minRange = 30;    
    auto last = vect.end();   

    using Iter = std::vector<int>::iterator;
     
    for (auto first = vect.begin(); first < last; ++first) {
        int rng = last - first;
        int minRng = rng / countCore;
        while (minRng < minRange && countCore!=1) {
            --countCore;
            minRng = rng / countCore;
        }
        
        std::vector<std::future<Iter>> vecFut;
        std::vector<std::packaged_task<Iter(Iter, Iter)>> vecPack;
        std::vector<std::future<void>> vecRes;

        for (int i = 0; i < countCore; ++i) {
            std::packaged_task<Iter(Iter, Iter)> p_t(find_min<Iter>); 
            vecFut.push_back(p_t.get_future());
            Iter end;
            if (i == countCore - 1)
                end = last - 1;
            else
                end = first + (i + 1) * minRng - 1;
            Iter start = first + i * minRng;            
            auto tmp = std::async(std::move(p_t), start, end);            
        }
        for (int i = 0; i < countCore; ++i) {
            vecFut[i].wait();
        }

        std::vector<Iter> vecResMin;
        for (int i = 0; i < countCore; ++i) {
            vecResMin.push_back(vecFut[i].get());
        }

        Iter resMin = vecResMin[0];
        for (auto i : vecResMin) {
            if (*i < *resMin)
                resMin = i;
        }

        if (resMin != first) {
            int temp = *first;
            *first = *resMin;
            *resMin = temp;
        }        
    }//for
    
    promis.set_value(vect);
}




int main()
{
    int size = 10000;
    std::vector<int> vect(size);
    std::random_device rand;
    std::mt19937 gener{ rand()};
    std::uniform_int_distribution<int> distr(0, 1000);    
    for (int i = 0; i < size; ++i) {
        vect[i] = distr(gener);
    }
    
    std::promise<std::vector<int>> promis;
    std::future<std::vector<int>> futur = promis.get_future();
    auto result = std::async(choice_sort, vect, std::move(promis));
    futur.wait();
    auto resVec = futur.get();
    for (auto i : resVec) {
        std::cout << std::setw(5) << i;
    }
}
