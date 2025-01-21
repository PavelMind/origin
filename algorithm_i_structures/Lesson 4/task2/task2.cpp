#include <iostream>
#include <string>
#include "print.h"


void append_to_dynamic_array(int* arr, int& logical_size, int& actual_size, int var) {
    if (logical_size >= actual_size) {
        actual_size = actual_size * 2;
        int* temp = new int[actual_size];
        /*for (int i = 0; i < logical_size; ++i) {
            temp[i] = arr[i];
        }*/
        memcpy(temp, arr, logical_size * sizeof(int));
        delete[] arr;
        arr = temp;
    }
    arr[logical_size] = var;
    ++logical_size;
}


int main()
{
    setlocale(LC_ALL, "Russian");
    int logSize, realSize;
    while (true) {
        std::cout << "Введите фактический размер динамического массива: ";
        std::cin >> realSize;
        std::cout << "Введите логический размер динамического массива: ";
        std::cin >> logSize;
        if (logSize > realSize || realSize < 1) {
            std::cout << "Ошибка! Неправильные размеры\n";
            continue;
        }
        break;
    }
    int* arr = new int[logSize];
    for (int i = 0; i < logSize; ++i) {
        int input;
        std::cout << "arr[" << i << "] = ";
        std::cin >> input;
        arr[i] = input;
    }
    print_dynamic_array(arr, logSize, realSize);
    int add;
    while (true) {
        std::cout << "Введите число для добавления (0 - выход): ";
        std::cin >> add;
        if (add == 0) { 
            std::cout << "Спасибо. ";
            print_dynamic_array(arr, logSize, realSize);
            break;
        }
        append_to_dynamic_array(arr, logSize, realSize, add);
        print_dynamic_array(arr, logSize, realSize);
    }
    
    
    delete[] arr;
}

