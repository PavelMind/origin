#pragma once
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <type_traits>
#include <future>
#include "safe_queue.h"

//template<typename Ret, typename ...Ar>
class my_thread_pool {
    std::atomic<int> maxThread;
    std::vector<std::thread> vecThreads;
    safe_queue_o/*<function_wrapp>*/ sQueue;
    std::atomic<bool> toStopThread{ false };    
public:
    my_thread_pool(int m) {
        if (m > 0)
            maxThread = m;
        else
            maxThread = std::thread::hardware_concurrency();
        for (int i = 0; i < maxThread; ++i) {
            std::thread t(&my_thread_pool::run, this);
            vecThreads.push_back(std::move(t));
            vecThreads[i].detach();
        }
    }

    ~my_thread_pool() {
        std::cout << "bagin Destruct of POOL\n";
        toStopThread.store(true);
        sQueue.toStopThread.store(true);
        sQueue.c_v.notify_all();
        while (maxThread.load() >  0) {
            using namespace std;
            std::this_thread::sleep_for(100ms);
        }
    }

    void run() {
        while (!toStopThread) {
            auto f = sQueue.pop();
            if (toStopThread.load()) {
                //std::cout << maxThread<<"maxThrd-- ";
                
                //std::cout << maxThread<<"\n";
                break;
            }
            else
                f();
        }
        maxThread.fetch_sub(1);
    }

    template<typename TypeF>
    std::future<typename std::result_of<TypeF()>::type> submit(TypeF f) {
        using type_of_result = typename std::result_of<TypeF()>::type;
        std::packaged_task<type_of_result()> task(std::move(f));
        std::future<type_of_result> res(task.get_future());
        sQueue.push(std::move(task));
        return res;
    }
};