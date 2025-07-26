#pragma once
#include <thread>
#include <vector>
#include <chrono>
#include "safe_queue.h"

template<typename Ret, typename ...Ar>
class thread_pool {
    std::atomic<int> maxThread;
    std::vector<std::thread> vecThreads;
    safe_queue<Ret(Ar...)> sQueue;
    std::atomic<bool> toStopThread{ false };
public:
    thread_pool(int m) {
        /*if (m > 0)
            maxThread = m;
        else*/
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
            std::function<Ret(Ar...)> f = sQueue.pop();
            if (toStopThread.load()) {
                maxThread.fetch_sub(1);
                break;
            }
            else
                f();
        }
    }

    void submit(std::function<Ret(Ar...)> task) {
        sQueue.push(std::move(task));
    }
};