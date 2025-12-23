#pragma once
#include <mutex>
#include <queue>
#include <condition_variable>
#include <functional>
#include <atomic>

class thread_pool;

class safe_queue {
    std::queue<std::function<void(void)> > Queue;
    std::condition_variable c_v;
    std::mutex mutx;
    std::atomic<bool> toStopThread{ false };
    
public:    
    safe_queue() {}
    friend class thread_pool;

    void push(std::function<void(void)>&& fu) {
        std::lock_guard<std::mutex> mut(mutx);
        Queue.push(std::move(fu));
        c_v.notify_all();
    }

    auto pop() {
        std::unique_lock<std::mutex> mut(mutx);
        c_v.wait(mut, [&]() {return !Queue.empty() || toStopThread.load() ; });
        if (toStopThread.load()) {
            return std::function<void(void)> (nullptr);
        }
        auto top = Queue.front();
        Queue.pop();
        return top;
    }

    bool empty() {
        return Queue.empty();
    }
};
