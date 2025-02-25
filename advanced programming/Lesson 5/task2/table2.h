#pragma once

template<typename T>
class table2 {
    T** arr;
    size_t line;
    size_t column;
public:
    table2(int a, int b) : line(a), column(b) {
        arr = new T * [a];
        for (int i = 0; i < a; ++i) {
            arr[i] = new T[b];
        }
    }
    ~table2() {
        for (int i = 0; i < line; ++i) {
            delete arr[i];
        }
        delete[] arr;
    }

    

    T* operator[](int i) {
        
        return arr[i];
    }

    int Size() const {
        return line * column;
    }
};