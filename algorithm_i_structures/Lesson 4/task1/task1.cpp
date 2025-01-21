#include <iostream>

void print_dynamic_array(int* arr, int logical_size, int actual_size) {  
    int i = 0;
    for (; i < logical_size; ++i) {        
        std::cout << arr[i] << " ";
    }
    for (; i < actual_size; ++i) {
        std::cout << "_ ";
    }

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
        if (logSize > realSize) {
            std::cout << "Ошибка! Фактический размер должен быть больше или равен логическому.\n";
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
    delete[] arr;
}

