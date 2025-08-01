#pragma once
#include <iostream>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <atomic>
#include <memory>


//template<typename Ret, typename ...Ar>
class my_thread_pool/*<Ret,Ar...>*/;


class function_wrapp_o {
    struct fu_base {
        virtual void call() = 0;
        virtual ~fu_base() {}
    };

    template<typename TypeFunc>
    struct fu_impl: public fu_base {
        TypeFunc f;
        fu_impl(TypeFunc&& o) : f(std::move(o)) {}
        void call() { f(); }
    };
    std::unique_ptr<fu_base> func;
public:
    function_wrapp_o() : func(nullptr) {}

    template<typename TypeFunc>
    function_wrapp_o(TypeFunc&& f): func(new fu_impl<TypeFunc>(std::move(f))) {  }

    function_wrapp_o(function_wrapp_o& oth) = delete;
    function_wrapp_o(const function_wrapp_o& oth) = delete;
    function_wrapp_o& operator = (function_wrapp_o& oth) = delete;

    function_wrapp_o(function_wrapp_o&& oth) :
        func (std::move(oth.func))   { }
    function_wrapp_o& operator = (function_wrapp_o&& oth) {
        func = std::move(oth.func); 
        return *this; 
    }
    void operator ()() { func->call(); }
};


//template<typename TypeF>
class safe_queue_o {
    std::queue<function_wrapp_o > Queue;
    std::condition_variable c_v;
    std::mutex mutx;
    std::atomic<bool> toStopThread{ false };

public:
    safe_queue_o() {}
    friend class my_thread_pool;

    template<typename TypeF>
    void push(TypeF&& fu) {
        std::lock_guard<std::mutex> mut(mutx);
        Queue.push(std::move(fu));
        c_v.notify_all();
    }
    //template<typename TypeF>
    auto pop() {
        std::unique_lock<std::mutex> mut(mutx);
        c_v.wait(mut, [&]() {return !Queue.empty() || toStopThread.load(); });
        if (toStopThread.load()) {
            std::cout << "in POP return () of stop\n";
            return function_wrapp_o();
        }
        auto top = std::move(Queue.front());
        Queue.pop();
        return top;
    }

    bool empty() {
        return Queue.empty();
    }
};