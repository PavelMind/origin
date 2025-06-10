#include <iostream>
#include <chrono>
#include <string>
#include <mutex>
#include "set include.h"

#ifdef INCLUDE_WITH_TEMPLATE  //into "set include.h"
#include "thread_pool_tmplt.h"
#endif // INCLUDE_WITH_TEMPLATE

#ifdef INCLUDE_WITH_PASKAGED_TASK
#include "thread_pool_pt.h"
#endif // INCLUDE_WITH_PASKAGED_TASK

#ifdef INCLUDE_WITH_FUNCTION
#include "thread_pool_f.h"
#endif // INCLUDE_WITH_FUNCTION




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

std::string func2(int i) {
    using namespace std;
    std::this_thread::sleep_for(500ms);
    std::string str{ "abcdefghijklmnopqrs" };
    str.resize(i);
    return str;
}


int main()
{
    
#if INCLUDE_WITH_TEMPLATE
    
    thread_pool<void, void> TP;
    thread_pool<std::string, int> TP2;
    int countTime = 0;

    while (countTime<10) {
        std::packaged_task<void(void)> task1(func1), task2(func1);
        std::future futur1 = task1.get_future();
        std::future futur2 = task2.get_future();
        TP.submit(task1);
        TP.submit(task2);

        std::packaged_task<std::string(int)> task3(func2);
        std::future futur3 = task3.get_future();
        TP2.submit(task3, countTime);
        
        futur1.wait();
        futur2.wait();
        futur3.wait();
        
        using namespace std;
        std::this_thread::sleep_for(1s);

        auto res = futur3.get();
        std::cout << res << std::endl;

        ++countTime;
    }
#endif // INCLUDE_WITH_TEMPLATE

#if INCLUDE_WITH_PASKAGED_TASK

    thread_pool TPool;
    int countTime = 0;
    while (countTime<10) {
        std::packaged_task<void(void)> task1(func1), task2(func1);
        std::future futur1 = task1.get_future();
        std::future futur2 = task2.get_future();
        TPool.submit(std::move(task1));
        TPool.submit(std::move(task2));

        futur1.wait();
        futur2.wait();
        using namespace std;
        std::this_thread::sleep_for(1s);
        ++countTime;
    }
#endif //INCLUDE_WITH_PASKAGED_TASK

#if INCLUDE_WITH_FUNCTION

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

#endif // INCLUDE_WITH_FUNCTION
}
