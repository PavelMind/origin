#pragma once
#include <iostream>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <atomic>
#include <memory>
#include <tuple>




class my_thread_pool_a;


class function_wrapp_a {
    struct fu_base {
        virtual void call() = 0;
        virtual ~fu_base() {}
    };

    template<typename TypeFunc, typename ...TpArgs>
    struct fu_impl: public fu_base {
        TypeFunc f;
        std::tuple<TpArgs...> argList;

        fu_impl(TypeFunc&& o, TpArgs... args) : f(std::move(o)), argList(args...) {  }
        void call() { std::apply(f, argList); }
    };
    std::unique_ptr<fu_base> func;
public:
    function_wrapp_a() : func(nullptr) {}

    template<typename TypeFunc, typename ...TpArgs>
    function_wrapp_a(TypeFunc&& f, TpArgs... args):
        func(new fu_impl<TypeFunc, TpArgs...>(std::move(f), args...)) {  }
    
    
    function_wrapp_a(function_wrapp_a& oth) {
        func = std::move(oth.func);
    }
    function_wrapp_a& operator = (function_wrapp_a& oth) {
        func = std::move(oth.func); return *this; 
    }

    function_wrapp_a(function_wrapp_a&& oth) :
        func (std::move(oth.func))   { }
    function_wrapp_a& operator = (function_wrapp_a&& oth) {
        func = std::move(oth.func); 
        return *this; 
    }
    void operator ()() { func->call(); }
};



class safe_queue_a {
    std::queue<function_wrapp_a > Queue;
    std::condition_variable c_v;
    std::mutex mutx;
    std::atomic<bool> toStopThread{ false };

public:
    safe_queue_a() {}
    friend class my_thread_pool_a;

    template<typename TypeF, typename ...TpArgs>
    void push(TypeF&& fu, TpArgs... args) {
        std::lock_guard<std::mutex> mut(mutx);
        function_wrapp_a fwrap(std::move(fu), args...);
        Queue.push(fwrap);
        c_v.notify_all();
    }
    
    function_wrapp_a pop() {
        std::unique_lock<std::mutex> mut(mutx);
        c_v.wait(mut, [&]() {return !Queue.empty() || toStopThread.load(); });
        
        if (toStopThread.load()) {
            function_wrapp_a err();
            return err;
        }
        auto top = Queue.front();
        Queue.pop();
        return top;
    }

    bool empty() {
        return Queue.empty();
    }
};