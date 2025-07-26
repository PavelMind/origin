#pragma once
#include <mutex>
#include <queue>
#include <condition_variable>
#include <string>
#include <atomic>



class thread_pool_s;


class safe_queue_s {
    std::queue<std::string> Queue;
    std::condition_variable c_v;
    std::mutex mutx;
    std::atomic<bool> toStopThread{ false };

public:
    safe_queue_s() {}
    friend class thread_pool_s;

    void push(std::string&& site) {
        std::lock_guard<std::mutex> mut(mutx);
        Queue.push(std::move(site));
        c_v.notify_all();
    }

    auto pop() {
        std::unique_lock<std::mutex> mut(mutx);
        c_v.wait(mut, [&]() {return !Queue.empty() || toStopThread.load(); });
        if (toStopThread.load()) {
            return std::string{};
        }
        auto top = Queue.front();
        Queue.pop();
        return top;
    }

    bool empty() {
        return Queue.empty();
    }
};