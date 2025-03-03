#pragma once
#include <exception>
#include <stdexcept>

namespace my {

    template<typename T>
    class vector {
        T* arr;
        size_t _size;
        size_t _reserved;

        void alloc(int);
    public:
        vector();
        vector(size_t sz);
        vector(vector&);
#if 0
        vector(std::initializer_list<T> list);
#endif
        ~vector();

        void operator =(vector&);

        size_t size();
        size_t capacity();
        T& at(int);
        void push_back(T);
    };

}