#pragma once
#include "set include.h"
#if INCLUDE_WITH_FUNCTION
#include <thread>
#include <vector>
#include "safe_queue_f.h"


class thread_pool {
    std::atomic<int> maxThread;
    std::vector<std::thread> vecThreads;
    safe_queue sQueue;
    std::atomic<bool> toStopThread{ false };
public:
    thread_pool() {
        maxThread = std::thread::hardware_concurrency();
        for (int i = 0; i < maxThread; ++i) {
            std::thread t(&thread_pool::work, this);
            vecThreads.push_back(std::move(t));
            vecThreads[i].detach();
        }
    }

    ~thread_pool() {
        toStopThread.store(true);
        sQueue.toStopThread.store(true);
        sQueue.c_v.notify_all();
        while(maxThread.load()!=0) {
            using namespace std;
            std::this_thread::sleep_for(100ms);
        }
    }

    void work() {
        while (!toStopThread) {
            std::function<void(void)> f = sQueue.pop();
            if (toStopThread.load()) {
                maxThread.fetch_sub(1);
                break;
            }
            else
                f();
        }
    }

    void submit(std::function<void(void)> task) {
        sQueue.push(std::move(task));
    }
};

#endif // INCLUDE_WITH_FUNCTION