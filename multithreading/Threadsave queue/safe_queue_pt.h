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
public:
    safe_queue() {}
    friend class thread_pool;

    void push(std::packaged_task<void(void)>&& pt) {
        std::lock_guard<std::mutex> mut(mutx);
        Queue.push(std::move(pt));
        c_v.notify_all();
    }

    std::packaged_task<void(void)> get_and_pop() {
        std::lock_guard<std::mutex> mut(mutx);
        return Queue.front();
    }

    bool empty() {
        return Queue.empty();
    }
};

#endif // INCLUDE_WITH_PASKAGED_TASK
