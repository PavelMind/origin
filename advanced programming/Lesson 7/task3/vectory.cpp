#include "vectory.hpp"

namespace my {

    //template<typename int>
    void vector::alloc(int newSZ) {
        int* temp = new int[newSZ];
        _reserved = newSZ;
        size_t min = _size < newSZ ? _size : newSZ;
        _size = min;

        for (int i = 0; i < min; ++i) {
            temp[i] = arr[i];
        }
        delete[] arr;
        arr = temp;
    }

    //template<typename int>
    vector::vector() : _size(0), _reserved(4), arr(nullptr) {}

    //template<typename int>
    vector::vector(size_t sz) : _size(0), _reserved(sz), arr(nullptr) {
        if (sz <= 0) throw std::range_error("bad size");
        arr = new int[sz];
    }

    //template<typename int>
    vector::vector(vector& other) {
        _size = other._size;
        _reserved = other._reserved;
        for (int i = 0; i < _size; ++i) {
           this->at(i) = other.at(i);
        }
    }

#if 0
    //template<typename int>
    vector::vector(std::initializer_list<int> list) : _size(list.size()) {
        alloc(_size);
        arr = list.begin();
    }
#endif
    //template<typename int>
    vector::~vector() {
        if (arr != nullptr) {
            delete[] arr;
        }
    }

    //template<typename int>
    void vector::operator = (vector& other) {
        _size = other._size;
        _reserved = other._reserved;
        for (int i = 0; i < _size; ++i) {
            this->at(i) = other.at(i);
        }
    }

    //template<typename int>
    size_t vector::size() {
        return _size;
    }

    //template<typename int>
    size_t vector::capacity() {
        return _reserved;
    }

    //template<typename int>
    int& vector::at(int index) {
        if (index < 0 || index >= _size) {
            throw std::out_of_range("bad range");
        }
        return arr[index];
    }

    //template<typename int>
    void vector::push_back(int value) {
        if (_size == _reserved) {
            alloc(_reserved * 2);
        }
        arr[_size++] = value;
    }

}