#pragma once
#include <thread>
#include <vector>
#include <chrono>
#include <type_traits>
#include <future>
#include "safe_queue_arg.h"


class thread_pool_a {
    std::atomic<int> maxThread;
    std::vector<std::thread> vecThreads;
    safe_queue sQueue;
    std::atomic<bool> toStopThread{ false };    

    void run() {
        while (!toStopThread) {
            auto f = std::move(sQueue.pop());
            if (!toStopThread.load()) {
                f();
                f.deletFunc();
            }
            else
                break;
        }
        maxThread.fetch_sub(1);
    }
public:
    thread_pool_a(int m) {
        if (m > 0)
            maxThread = m;
        else
            maxThread = std::thread::hardware_concurrency();
        for (int i = 0; i < maxThread; ++i) {
            std::thread t(&thread_pool_a::run, this);
            vecThreads.push_back(std::move(t));
            vecThreads[i].detach();
        }
    }

    ~thread_pool_a() {
        toStopThread.store(true);
        sQueue.toStopThread.store(true);
        sQueue.c_v.notify_all();
        while (maxThread.load() >  0) {
            using namespace std;
            std::this_thread::sleep_for(100ms);
        }
    }

    
    template<typename TypeF, typename ...TpArgs>
    std::future<std::invoke_result_t<TypeF, TpArgs...>> submit(TypeF&& f, TpArgs&&... args)
    {
        using result_type = std::invoke_result_t<TypeF, TpArgs...>;        
        auto bound_f = std::bind(std::forward<TypeF>(f), std::forward<TpArgs>(args)...);
        std::packaged_task<result_type()> task(std::move(bound_f));
        std::future<result_type> res = task.get_future();
        sQueue.push([task = std::move(task)]() mutable {
            task();
            }
            //std::move(task)
        );
        return res;
    }
};