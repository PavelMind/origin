#include <iostream>
#include <thread>
#include <future>
#include <vector>
#include <algorithm>


template<typename It, typename Func>
void my_for_each(It first, It last, Func func) {
    int range = last - first;
    if (range < 50) {
        std::for_each(first, last, func);
    }
    else {
        It middle = first + range / 2;
        auto res1 = std::async(my_for_each<It, Func>, first, middle, func);
        my_for_each(middle, last, func);
    }

}

void foo(int& i) {
    i *= 2;
}

int main()
{
    
    std::vector<int> vect(201);
    for (auto i = 0; i < vect.size();++i) {
        vect[i] = i;
    }
    for (auto i : vect) {
        std::cout << i << " ";
    }
    using It = decltype(vect.begin());
    auto res = std::async(my_for_each<It, void(int&)>, vect.begin(), vect.end(), foo);
    res.wait();
    std::cout << "\n\n";
    for (auto i : vect) {
        std::cout << i << " ";
    }
}

