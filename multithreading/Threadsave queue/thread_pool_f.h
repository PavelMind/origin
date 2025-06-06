#pragma once
#include "set include.h"
#if INCLUDE_WITH_FUNCTION
#include <thread>
#include <vector>
#include "safe_queue_f.h"


class thread_pool {
    int maxCore;
    std::vector<std::thread> vecThreads;
    safe_queue sQueue;
    bool toStopThread = false;
public:
    thread_pool() {
        maxCore = std::thread::hardware_concurrency();
        for (int i = 0; i < maxCore; ++i) {
            std::thread t(&thread_pool::work, this, std::ref(sQueue.mutx));
            vecThreads.push_back(std::move(t));
            vecThreads[i].detach();
        }
    }

    ~thread_pool() {
        toStopThread = true;
    }

    void work(std::mutex& mtx) {
        while (true) {
            
            std::unique_lock<std::mutex> mut(mtx);
            sQueue.c_v.wait(mut, [&]() {return !sQueue.empty() || toStopThread; });
            if (toStopThread) {
                break;
            }
            std::function<void(void)> f = sQueue.get_and_pop();
            mut.unlock();
            f();
        }
    }

    void submit(std::function<void(void)> task) {
        sQueue.push(std::move(task));
    }
};

#endif // INCLUDE_WITH_FUNCTION