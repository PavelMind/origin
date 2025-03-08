#pragma once

namespace my {

    template<typename T>
    class unique_ptr {
        T* ptr;
    public:
        unique_ptr(T* p): ptr(p){}
        ~unique_ptr() {
            if(ptr) delete ptr;
        }
        unique_ptr(unique_ptr&) = delete;
        void operator =(unique_ptr&) = delete;

        unique_ptr(unique_ptr&& other) {
            ptr = other.ptr;
            other.ptr = nullptr;
        }

        T& operator *() {
            return *ptr;
        }
        T* release() {
            T* temp = ptr;
            ptr = nullptr;
            return temp;
        }
    };

}