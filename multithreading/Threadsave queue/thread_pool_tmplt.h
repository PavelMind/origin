#pragma once
#include "set include.h"
#if INCLUDE_WITH_TEMPLATE
#include <thread>
#include <vector>
#include <future>
#include "safe_queue_tmplt.h"

//namespace tmplt {

    template<typename Retur, typename... Arg>
    class thread_pool {
        int maxCore;
        std::vector<std::thread> vecThreads;
        safe_queue<Retur, Arg...> sQueue;
        bool toStopThread = false;
    public:
        thread_pool() {
            maxCore = std::thread::hardware_concurrency();
            for (int i = 0; i < maxCore; ++i) {
                vecThreads.push_back(std::thread(&thread_pool::work, this));
                vecThreads[i].join();
            }
        }
        void work() {
            while (true) {
                std::unique_lock<std::mutex> mut(sQueue.mutx);
                sQueue.c_v.wait(mut, [&]() {return !sQueue.empty() || toStopThread; });
                if (toStopThread) {
                    break;
                }
                dataTask<Retur, Arg> t = sQueue.get_and_pop();
                t.p_t(t.listArg);
            }
        }

        void submit(std::packaged_task<Retur(Arg...)>& task, Arg... a) {
            sQueue.push(task, a);
        }
    };





    template<typename Retur>
    class thread_pool <Retur, void> {
        int maxCore;
        std::vector<std::thread> vecThreads;
        safe_queue<Retur> sQueue;
        bool toStopThread = false;
    public:
        thread_pool() {
            maxCore = std::thread::hardware_concurrency();
            for (int i = 0; i < maxCore; ++i) {
                vecThreads.push_back(std::thread(&thread_pool::work, this));
                vecThreads[i].join();
            }
        }
        void work() {
            while (true) {
                std::unique_lock<std::mutex> mut(sQueue.mutx);
                sQueue.c_v.wait(mut, [&]() {return !sQueue.empty() || toStopThread; });
                if (toStopThread) {
                    break;
                }
                dataTask<Retur, void> t = sQueue.get_and_pop();
                t.p_t();
            }
        }

        void submit(std::packaged_task<Retur(void)>& task) {
            sQueue.push(task);
        }
    };

//}//namespase
#endif // INCLUDE_WITH_TEMPLATE