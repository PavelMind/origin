#pragma once
#include <mutex>
#include <queue>
#include <condition_variable>
#include <atomic>
#include <memory>



class thread_pool_a;

class function_wrapp {
    struct fu_base {
        virtual void call() = 0;
        virtual ~fu_base() {}
    };

    template<typename TypeFunc>
    struct fu_impl : public fu_base {
        TypeFunc f;
        fu_impl(TypeFunc&& o) : f(std::move(o)) {}
        void call() { f(); }
    };
    //std::unique_ptr<fu_base> func; // -> exception
    fu_base* func;
public:
    function_wrapp() : func(nullptr) {}

    template<typename TypeFunc>
    function_wrapp(TypeFunc&& f)/*: func(std::make_unique<TypeFunc>(std::move(f)))*/ {
        func = new fu_impl<TypeFunc>(std::move(f));
        //func = std::make_unique<fu_impl<TypeFunc>>(std::move(f));
    }

    ~function_wrapp() { 
        //delete func; 
    }

    void deletFunc() {
        delete func;
    }

    function_wrapp(function_wrapp& oth) = delete;
    function_wrapp& operator = (function_wrapp& oth) = delete;

    function_wrapp(function_wrapp&& oth) :
        func(std::move(oth.func)) {    }

    function_wrapp&& operator = (function_wrapp&& oth) {
        func = std::move(oth.func);
        return std::move (*this);
    }
    void operator ()() { func->call(); }
};

class safe_queue {
    std::queue<function_wrapp> Queue;
    std::condition_variable c_v;
    std::mutex mutx;
    std::atomic<bool> toStopThread{ false };
    friend class thread_pool_a;
public:
    safe_queue() {}
    
    template<typename TypeF>
    void push(TypeF&& fu) {
        std::lock_guard<std::mutex> mut(mutx);
        Queue.push(std::move(fu));
        c_v.notify_all();
    }
    
    function_wrapp&& pop() {
        std::unique_lock<std::mutex> mut(mutx);
        c_v.wait(mut, [&]() {return !Queue.empty() || toStopThread.load(); });
        
        if (toStopThread.load()) {
            return std::move(function_wrapp());
        }
        auto top = std::move(Queue.front());
        Queue.pop();
        return std::move(top);
    }

    bool empty() {
        return Queue.empty();
    }
};