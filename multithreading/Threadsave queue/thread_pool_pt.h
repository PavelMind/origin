#pragma once
#include "set include.h"
#if INCLUDE_WITH_PASKAGED_TASK
#include <thread>
#include <vector>
#include <future>
#include "safe_queue_pt.h"



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
        while (maxThread.load() != 0) {
            using namespace std;
            std::this_thread::sleep_for(100ms);            
        }
    }

    void work() {
        while (!toStopThread) { 
            auto& task = sQueue.pop();  
            if (toStopThread.load()) {
                maxThread.fetch_sub(1);                
                break;
            }
            else
                task();
        }
    }

    void submit(std::packaged_task<void(void)>&& task) {
        sQueue.push(std::move(task));
    }
};

#endif // INCLUDE_WITH_PASKAGED_TASK