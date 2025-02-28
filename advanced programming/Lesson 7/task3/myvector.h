#pragma once

#include <initializer_list>
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
        vector(std::initializer_list<T> list);

        size_t size();
        size_t capacity();
        T& at(int);
        void push_back(T);
    };




}