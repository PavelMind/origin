#include "myvector.h"

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
    vector<T>::vector(): _size(0), _reserved(4), arr(nullptr){}

    template<typename T>
    vector<T>::vector(size_t sz) :_size(0), _reserved(sz) {
        if (sz <= 0) throw std::range_error("bad size");
        arr = new T[sz];
    }

    template<typename T>
    vector<T>::vector(std::initializer_list<T> list) : _size(list.size()) {
        alloc(_size);
        arr = list.begin();        
    }

    template<typename T>
    size_t vector<T>::size(){
        return _size;
    }

    template<typename T>
    size_t vector<T>::capacity(){
        return _reserved;
    }

    template<typename T>
    T& vector<T>::at(int index){
        if (index < 0 || index >= _size) {
            throw std::out_of_range("bad range");
        }
        return arr[index];
    }

    template<typename T>
    void vector<T>::push_back(T value){
        if (_size == _reserved) {
            alloc(_reserved * 2);
        }
        arr[_size++] = value;
    }



}