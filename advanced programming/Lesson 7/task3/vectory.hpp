#pragma once
#include <exception>
#include <stdexcept>

namespace my {

    //template<typename int>
    class vector {
        int* arr;
        size_t _size;
        size_t _reserved;

        void alloc(int);
    public:
        vector();
        vector(size_t sz);
        vector(vector&);
#if 0
        vector(std::initializer_list<int> list);
#endif
        ~vector();

        void operator =(vector&);

        size_t size();
        size_t capacity();
        int& at(int);
        void push_back(int);
    };

}