#pragma once
#include <mutex>
#include <queue>
#include <condition_variable>
#include <string>
#include <atomic>
#include <future>
#include <utility>



class thread_pool_s;


class safe_queue_s {
    using task = std::packaged_task<std::string(std::string)>;
    std::queue<std::pair<task, std::string> > Queue;
    std::condition_variable c_v;
    std::mutex mutx;
    std::atomic<bool> toStopThread{ false };

public:
    safe_queue_s() {}
    friend class thread_pool_s;

    void push(std::pair<task, std::string>&& site) {
        std::lock_guard<std::mutex> mut(mutx);
        Queue.push(std::move(site));
        c_v.notify_all();
    }

    auto pop() {
        std::unique_lock<std::mutex> mut(mutx);
        c_v.wait(mut, [&]() {return !Queue.empty() || toStopThread.load(); });
        if (toStopThread.load()) {
            return std::move(std::pair<task, std::string>());
        }
        auto top = std::move(Queue.front());
        Queue.pop();
        return std::move(top);
    }

    bool empty() {
        return Queue.empty();
    }
};