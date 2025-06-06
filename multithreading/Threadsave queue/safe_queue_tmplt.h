#pragma once
#include "set include.h"
#if INCLUDE_WITH_TEMPLATE
#include <mutex>
#include <queue>
#include <condition_variable>
#include <future>

//namespace tmplt {


    template<typename Retur, typename... Arg>
    class thread_pool;

    template<typename Retur, typename... Arg>
    class dataTask {
        std::packaged_task<Retur(Arg...)> p_t{};
        std::initializer_list<Arg...> listArg;
    public:
        dataTask(std::packaged_task<Retur(Arg...)>&& pt, Arg... a) :p_t(std::move(pt)), listArg(a) {}
        
        template<typename Retur, typename... Arg>
        friend class safe_queue/*<Retur, Arg>*/;

        template<typename Retur, typename... Arg>
        friend class thread_pool/*<Retur, Arg>*/;
    };

    template<typename Retur, typename... Arg>
    class safe_queue {
        std::queue<dataTask<Retur, Arg...> > Queue;
        std::condition_variable c_v;
        std::mutex mutx;
    public:
        safe_queue() {}
        template<typename Retur, typename... Arg>
        friend class thread_pool;

        void push(std::packaged_task<Retur(Arg...)> pt, Arg... a) {
            std::lock_guard<std::mutex> mut(mutx);
            dataTask<Retur, Arg...> d(std::move(pt), a);
            Queue.push(std::move(d));
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






    template<typename Retur>
    class dataTask <Retur, void> {
        std::packaged_task<Retur(void)> p_t{};
        //std::initializer_list<Arg> listArg;
    public:
        dataTask(std::packaged_task<Retur(void)> pt) :p_t(pt) {}
                
        friend class safe_queue<Retur, void>;        
        friend class thread_pool<Retur, void>;
    };

    template<typename Retur>
    class safe_queue <Retur, void> {
        std::queue<dataTask<Retur, void> > Queue;
        std::condition_variable c_v;
        std::mutex mutx;
    public:
        safe_queue() {}
        template<typename Retur>
        friend class thread_pool<Retur, void>;

        void push(std::packaged_task<Retur(void)> pt) {
            std::lock_guard<std::mutex> mut(mutx);
            dataTask<Retur, void> d(pt);
            Queue.push(std::move(d));
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

//}//namespase
#endif // INCLUDE_WITH_TEMPLATE