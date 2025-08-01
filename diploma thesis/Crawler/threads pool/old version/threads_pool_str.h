#pragma once
#include <thread>
#include <vector>
#include <chrono>
#include <future>
#include <string>
#include "safe_queue_str.h"

//std::string strFoo(std::string s);



class thread_pool_s {
    std::atomic<int> maxThread;
    std::vector<std::thread> vecThreads;
    safe_queue_s sQueue;
    std::atomic<bool> toStopThread{ false };

    using TypeFuck = std::string(*)(std::string);
    TypeFuck func;
    using PC_task = std::packaged_task<std::string(std::string)>;
public:
    thread_pool_s(int, TypeFuck);
    ~thread_pool_s();
    void run();
    std::future<std::string> submit(std::string site);
};