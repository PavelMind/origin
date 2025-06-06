#pragma once
#include "set include.h"
#if INCLUDE_WITH_FUNCTION
#include <mutex>
#include <queue>
#include <condition_variable>
#include <functional>

class thread_pool;

class safe_queue {
    std::queue<std::function<void(void)> > Queue;
    std::condition_variable c_v;
    std::mutex mutx;
public:    
    safe_queue() {}
    friend class thread_pool;

    void push(std::function<void(void)>&& fu) {
        std::lock_guard<std::mutex> mut(mutx);
        Queue.push(std::move(fu));
        c_v.notify_all();
    }

    auto get_and_pop() {
        std::lock_guard<std::mutex> mut(mutx);
        return Queue.front();
    }

    bool empty() {
        return Queue.empty();
    }
};

#endif // INCLUDE_WITH_FUNCTION