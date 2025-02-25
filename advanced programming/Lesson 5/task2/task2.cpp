#include <iostream>
#include "table2.h" //variant 2

// varint 1
template<typename T>
class table {
    T** arr;
    size_t line;
    size_t column;
public:
    table(int a, int b) : line(a), column(b) {
        arr = new T*[a];
        for (int i = 0; i < a; ++i) {
            arr[i] = new T[b];            
        }
    }
    ~table() {
        for (int i = 0; i < line; ++i) {
            delete arr[i];
        }
        delete[] arr;
    }
    
    class tempIter {
        T* var;
    public:
        tempIter(T* _v):var(_v){}
        T& operator[](int clmn) {
            return var[clmn];
        }

        const T& operator[](const int clmn) const {
            return var[clmn];
        }
    };

    tempIter& operator[](int ln) {        
        tempIter temp (arr[ln]);
        return temp;
    }


    const tempIter& operator[](const int ln) const {
        const tempIter temp(arr[ln]);
        return temp;
    }

    int Size() const {
        return line * column;
    }
};



int main()
{
    auto test = table<int>(2, 3);
    test[0][0] = 4;
    std::cout << test[0][0]; // выводит 4

    std::cout << std::endl << test.Size();
}
