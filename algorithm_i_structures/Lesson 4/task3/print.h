#pragma once
#include <iostream>

void print_dynamic_array(int* arr, int logical_size, int actual_size) {
    int i = 0;
    std::cout << "Динамический массив: ";
    for (; i < logical_size; ++i) {
        std::cout << arr[i] << " ";
    }
    for (; i < actual_size; ++i) {
        std::cout << "_ ";
    }
    std::cout << std::endl;
}