#include "threads_pool_str.h"



thread_pool_s::thread_pool_s(int m, TypeFuck f): func(f) {
    if (m > 0)
        maxThread = m;
    else
        maxThread = std::thread::hardware_concurrency();
    for (int i = 0; i < maxThread; ++i) {
        std::thread t(&thread_pool_s::run, this);
        vecThreads.push_back(std::move(t)); 
        
    }
    
    
}

thread_pool_s::~thread_pool_s() {
    toStopThread.store(true);
    sQueue.toStopThread.store(true);
    sQueue.c_v.notify_all();
    for (auto& thrd : vecThreads) {
        if (thrd.joinable())
            thrd.join();
    }
}

void thread_pool_s::run() {
    while (!toStopThread) {
        std::pair<PC_task, std::string> task = sQueue.pop();
        if (!toStopThread.load()) {
            auto site = task.second;
            task.first(site);
        }
        else
            break;
    }
    maxThread.fetch_sub(1);
}

std::future<std::string> thread_pool_s::submit( std::string site) {    
    PC_task task(std::move(func));
    std::future<std::string> res(task.get_future());
    std::pair< PC_task, std::string> tmp( std::move(task), site );
    sQueue.push(std::move(tmp));
    return res;
}
