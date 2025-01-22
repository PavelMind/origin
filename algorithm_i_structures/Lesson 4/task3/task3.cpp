#include <iostream>
#include <windows.h>
#include <string>
#include "print.h"

 
void remove_dynamic_array_head(int*& arr, int& logical_size, int& actual_size) {
    --logical_size;
    if (logical_size == 0) {
        actual_size = 1;
        arr[0] = 0;
        return;
    }
    int third = actual_size / 3;  

    if (logical_size <= third && third > 0) {
        actual_size = third;
        int* temp = new int[actual_size];
        for (int i = 0; i < logical_size; ++i) {
            temp[i] = arr[i + 1];
        }        
        delete[] arr;
        arr = temp;
    }
    else {
        for (int i = 0; i < logical_size; ++i) {
            arr[i] = arr[i + 1];
        }
    }
}


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
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
    int* arr = new int[realSize];
    for (int i = 0; i < logSize; ++i) {
        int input;
        std::cout << "arr[" << i << "] = ";
        std::cin >> input;
        arr[i] = input;
    }
    print_dynamic_array(arr, logSize, realSize);
    std::string add;
    
    while (true) {
        
        std::cout << "Введите \"да\" или 1 для удаления 1го элемента(другое- для выхода): ";
        std::cin >> add;
        if (add == "да" || add =="1") {
            remove_dynamic_array_head(arr, logSize, realSize);
            if (logSize <= 0) {
                std::cout << "Массив пуст!";
                break;
            }
            print_dynamic_array(arr, logSize, realSize);            
            continue;
        }
        std::cout << "Конец. ";
        print_dynamic_array(arr, logSize, realSize);
        break;
    }


    delete[] arr;
}

