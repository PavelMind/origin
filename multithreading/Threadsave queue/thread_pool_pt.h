#pragma once
#include "set include.h"
#if INCLUDE_WITH_PASKAGED_TASK
#include <thread>
#include <vector>
#include <future>
#include "safe_queue_pt.h"



class thread_pool {
    int maxCore;
    std::vector<std::thread> vecThreads;
    safe_queue sQueue;
    bool toStopThread = false;
public:
    thread_pool() {
        maxCore = std::thread::hardware_concurrency();
        for (int i = 0; i < maxCore; ++i) {
            std::thread t(&thread_pool::work, this);
            vecThreads.push_back(std::move(t));
            vecThreads[i].detach();
        }
    }

    ~thread_pool() {
        toStopThread = true;
    }

    void work() {
        while (true) {
            std::unique_lock<std::mutex> mut(sQueue.mutx);
            sQueue.c_v.wait(mut, [&]() {return !sQueue.empty() || toStopThread; });
            if (toStopThread) {
                break;
            }
            auto t = sQueue.get_and_pop();            
        }
    }

    void submit(std::packaged_task<void(void)>&& task) {
        sQueue.push(std::move(task));
    }
};

#endif // INCLUDE_WITH_PASKAGED_TASK