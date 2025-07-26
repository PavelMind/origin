#pragma once
#include <thread>
#include <vector>
#include <chrono>
#include "safe_queue_str.h"

class thread_pool_s {
    std::atomic<int> maxThread;
    std::vector<std::thread> vecThreads;
    safe_queue_s sQueue;
    std::atomic<bool> toStopThread{ false };
public:
    thread_pool_s(int);
    ~thread_pool_s();
    void run();
    void submit(std::string&& site);
};