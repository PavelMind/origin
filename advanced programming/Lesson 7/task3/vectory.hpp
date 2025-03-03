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

#if 1
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

namespace my {

    template<typename T>
    void vector<T>::alloc(int newSZ) {
        T* temp = new T[newSZ];
        _reserved = newSZ;
        size_t min = _size < newSZ ? _size : newSZ;
        _size = min;

        for (int i = 0; i < min; ++i) {
            temp[i] = arr[i];
        }
        delete[] arr;
        arr = temp;
    }

    template<typename T>
    vector<T>::vector() : _size(0), _reserved(4), arr(nullptr) {}

    template<typename T>
    vector<T>::vector(size_t sz) : _size(0), _reserved(sz), arr(nullptr) {
        if (sz <= 0) throw std::range_error("\nbad size!\n");
        arr = new T[sz];
    }

    template<typename T>
    vector<T>::vector(vector& other) {
        if (_reserved < other._size) {
            alloc(other._size);
        }
        _reserved = other._reserved;
        _size = other._size;
        for (int i = 0; i < _size; ++i) {
            arr[i] = other.arr[i];
        }
    }

#if 1
    template<typename T>
    vector<T>::vector(std::initializer_list<T> list) : _reserved(list.size()), _size(0) {
        arr = new T[_reserved];
        for (auto& item : list) {
            arr[_size++] = item;
        }
    }
#endif
    template<typename T>
    vector<T>::~vector() {
        if (arr != nullptr) {
            delete[] arr;
        }
    }

    template<typename T>
    void vector<T>::operator = (vector& other) {
        if (_reserved < other._size) {
            alloc(other._size);
        }
        _size = other._size;
        _reserved = other._reserved;        
        for (int i = 0; i < _size; ++i) {
            arr[i] = other.arr[i];
        }
    }

    template<typename T>
    size_t vector<T>::size() {
        return _size;
    }

    template<typename T>
    size_t vector<T>::capacity() {
        return _reserved;
    }

    template<typename T>
    T& vector<T>::at(int index) {
        if (index < 0 || index >= _size) {
            throw std::out_of_range("\nbad range!");
        }
        return arr[index];
    }

    template<typename T>
    void vector<T>::push_back(T value) {
        if (_size == _reserved) {
            alloc(_reserved * 2);
        }
        arr[_size++] = value;
    }

}