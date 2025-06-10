#pragma once
#include "set include.h"
#if INCLUDE_WITH_PASKAGED_TASK
#include <mutex>
#include <queue>
#include <condition_variable>
#include <future>

class safe_queue {
    std::queue<std::packaged_task<void(void)> > Queue;
    std::condition_variable c_v;
    std::mutex mutx;
    std::atomic<bool> toStopThread{ false };
public:
    safe_queue() {}
    friend class thread_pool;

    void push(std::packaged_task<void(void)>&& pt) {
        std::lock_guard<std::mutex> mut(mutx);
        Queue.push(std::move(pt));
        c_v.notify_all();
    }

    auto& pop() {
        std::unique_lock<std::mutex> mut(mutx);
        c_v.wait(mut, [&]() {return !Queue.empty() || toStopThread.load() ; });
        if (toStopThread.load()) {
            std::packaged_task<void(void)> temp;
            auto& g = temp; 
            return g;
        }
        auto& top = Queue.front();
        Queue.pop();
        return top;
    }

    bool empty() {
        return Queue.empty();
    }
};

#endif // INCLUDE_WITH_PASKAGED_TASK
