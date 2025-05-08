#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <vector>

void initVec(std::vector<int>& vec, int size, int m) {
    vec.resize(size);
    for (int i = 0; i < size; ++i) {
        vec[i] = i + m;
    }
}


using iterat = std::vector<int>::iterator;

void  summIt(iterat v1, iterat v2, iterat res, int size) {

    for (int i = 0; i < size; ++i) {
        res[i] = v1[i] + v2[i];
    }

}


auto dimension(std::vector<int> v1, std::vector<int> v2, int countT) {    
    int size = v1.size();
    std::vector<int> result(size);
    std::vector<std::thread> vecT;

    auto startTime = std::chrono::steady_clock::now();

    for (int i = 0; i < countT; ++i) {
        int t = size % countT;
        int newSize = size / countT;
        
        int rng = 0;        
        rng += newSize * i;
        rng += (i < t ? i : t);
        if (i < t)
            ++newSize;
        
        std::thread thrd(summIt, v1.begin() + rng, v2.begin() + rng, result.begin() + rng, newSize);
        vecT.push_back(std::move(thrd));        
    }
    for (int i = 0; i < countT; ++i) {
        vecT[i].join();
    }

    auto endTime = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::ratio<1,1>> time = endTime - startTime;
    return time;
}

auto run(std::vector<int> v1, std::vector<int> v2, int size, int countT) {
    initVec(v1, size, 1);
    initVec(v2, size, 8);
    auto time = dimension(v1, v2, countT);
    return time;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    std::cout << "Аппаратных ядер: " << std::thread::hardware_concurrency() << std::endl;

    std::vector<int> v1, v2;

    // //первый запуск всегда в 2-3 раза дольше
    //int size = 1000;
    //int cntThread = 3;    
    //auto time2 = run(v1, v2, size, cntThread);
    //std::cout <<"\n"<< time2.count();
    //time2 = run(v1, v2, size, cntThread);
    //std::cout << "\n" << time2.count();
    //time2 = run(v1, v2, size, cntThread);
    //std::cout << "\n" << time2.count();
    //auto time3 = run(v1, v2, size, cntThread);
    //std::cout << "\n" << time3.count();

    
    std::cout << std::endl << std::left;
    std::cout << std::setw(11) << " " << std::setw(11) << 1000 << std::setw(11) << 10000 <<
        std::setw(11) << 100'000 << std::setw(11) << 1'000'000 << std::endl;

    std::cout << std::setw(11) <<"1 поток" 
        << std::setw(11) << run(v1, v2, 1000, 1).count()
        << std::setw(11) << run(v1, v2, 10'000, 1).count()
        << std::setw(11) << run(v1, v2, 100'000, 1).count()
        << std::setw(11) << run(v1, v2, 1'000'000, 1).count() << std::endl;

    std::cout << std::setw(11) << "2 потока"
        << std::setw(11) << run(v1, v2, 1000, 2).count()
        << std::setw(11) << run(v1, v2, 10'000, 2).count()
        << std::setw(11) << run(v1, v2, 100'000, 2).count()
        << std::setw(11) << run(v1, v2, 1'000'000, 2).count() << std::endl;

    std::cout << std::setw(11) << "4 потока"
        << std::setw(11) << run(v1, v2, 1000, 4).count()
        << std::setw(11) << run(v1, v2, 10'000, 4).count()
        << std::setw(11) << run(v1, v2, 100'000, 4).count()
        << std::setw(11) << run(v1, v2, 1'000'000, 4).count() << std::endl;

    std::cout << std::setw(11) << "8 потоков"
        << std::setw(11) << run(v1, v2, 1000, 8).count()
        << std::setw(11) << run(v1, v2, 10'000, 8).count()
        << std::setw(11) << run(v1, v2, 100'000, 8).count()
        << std::setw(11) << run(v1, v2, 1'000'000, 8).count() << std::endl;

    std::cout << std::setw(11) << "16 потоков"
        << std::setw(11) << run(v1, v2, 1000, 16).count()
        << std::setw(11) << run(v1, v2, 10'000, 16).count()
        << std::setw(11) << run(v1, v2, 100'000, 16).count()
        << std::setw(11) << run(v1, v2, 1'000'000, 16).count() << std::endl;

    std::cout << std::setw(11) << "32 потока"
        << std::setw(11) << run(v1, v2, 1000, 32).count()
        << std::setw(11) << run(v1, v2, 10'000, 32).count()
        << std::setw(11) << run(v1, v2, 100'000, 32).count()
        << std::setw(11) << run(v1, v2, 1'000'000, 32).count() << std::endl;
}
