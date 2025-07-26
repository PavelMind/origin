#include "threads_pool_str.h"

thread_pool_s::thread_pool_s(int m) {
    if (m > 0)
        maxThread = m;
    else
        maxThread = std::thread::hardware_concurrency();
    for (int i = 0; i < maxThread; ++i) {
        std::thread t(&thread_pool_s::run, this);
        vecThreads.push_back(std::move(t));
        vecThreads[i].join();
    }
}

thread_pool_s::~thread_pool_s() {
    toStopThread.store(true);
    sQueue.toStopThread.store(true);
    sQueue.c_v.notify_all();
}

void thread_pool_s::run() {
    while (!toStopThread) {
        std::string s = sQueue.pop();

    }
}

void thread_pool_s::submit(std::string&& site) {
    sQueue.push(std::move(site));
}