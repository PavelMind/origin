#pragma once
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <type_traits>
#include <future>
#include "safe_queue_arg.h"

//template<typename Ret, typename ...Ar>
class my_thread_pool_a {
    std::atomic<int> maxThread;
    std::vector<std::thread> vecThreads;
    safe_queue_a/*<function_wrapp>*/ sQueue;
    std::atomic<bool> toStopThread{ false };    
public:
    my_thread_pool_a(int m) {
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

    ~my_thread_pool_a() {
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
                break;
            }
            else
                f();
        }
        maxThread.fetch_sub(1);
    }

    /*template<typename TypeF>
    std::future<typename std::result_of<TypeF(int, int)>::type> submit(TypeF f, int a, int b) {
        using type_of_result = typename std::result_of<TypeF(int, int)>::type;
        std::packaged_task<type_of_result(int, int)> task(std::move(f));
        std::future<type_of_result> res(task.get_future());
        sQueue.push(std::move(task), a,b);
        return res;
    }*/

    template<typename TypeF, typename ...TpArgs>
    std::future<typename std::result_of<TypeF(TpArgs...)>::type>
        submit(TypeF f, TpArgs... args) 
    {
        using type_of_result = typename std::result_of<TypeF(TpArgs...)>::type;
        std::packaged_task<type_of_result(TpArgs...)> task(std::move(f));
        std::future<type_of_result> res(task.get_future());
        sQueue.push(std::move(task), args...);
        return res;
    }
};