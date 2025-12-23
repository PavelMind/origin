#include <iostream>
#include <chrono>
#include <string>
#include <mutex>
#include "thread_pool_f.h"




void print(std::string str) {
    static std::mutex mtx;
    std::lock_guard<std::mutex> mut(mtx);
    std::cout << str << "\n";
}

void func1() {
    using namespace std;
    std::this_thread::sleep_for(500ms);
    print("func1");
}


int main()
{
    thread_pool TPool;
    int countTime = 0;
    while (countTime < 3) {
        std::function<void(void)> task1(func1), task2(func1);        
        TPool.submit(task1);
        TPool.submit(task2);
        using namespace std;
        std::this_thread::sleep_for(1s);
        ++countTime;
    }

}
