#pragma once
#include <mutex>
#include <queue>
#include <condition_variable>
#include <functional>
#include <atomic>


template<typename Ret, typename ...Ar>
class thread_pool/*<Ret,Ar...>*/;

template<typename Ret, typename ...Ar>
class safe_queue {
    std::queue<std::function<Ret(Ar...)> > Queue;
    std::condition_variable c_v;
    std::mutex mutx;
    std::atomic<bool> toStopThread{ false };

public:
    safe_queue() {}
    friend class thread_pool<Ret(Ar...)>;

    void push(std::function<Ret(Ar...)>&& fu) {
        std::lock_guard<std::mutex> mut(mutx);
        Queue.push(std::move(fu));
        c_v.notify_all();
    }

    auto pop() {
        std::unique_lock<std::mutex> mut(mutx);
        c_v.wait(mut, [&]() {return !Queue.empty() || toStopThread.load(); });
        if (toStopThread.load()) {
            return std::function<Ret(Ar...)>(nullptr);
        }
        auto top = Queue.front();
        Queue.pop();
        return top;
    }

    bool empty() {
        return Queue.empty();
    }
};