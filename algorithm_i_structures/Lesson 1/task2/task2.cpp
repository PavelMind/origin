#include <iostream>
#include <windows.h>

struct arrey {
    int arr[9]{ 14, 16, 19, 32, 32, 32, 56, 69, 72 };
    size_t size = 9;
    int& operator[](int n) { return arr[n]; }
};

int func(arrey arr, int const n) {
    int left = 0;
    int right = arr.size - 1;
    int middle;
    if (arr[right] <= n) return 0;
    if (arr[0] > n) return arr.size;

    while (true) {
        middle = (right + left)/ 2;
        if ( n >= arr[middle] && (right - left) > 1) {
            left = middle;
            continue;
        }
        else if (n < arr[middle] && (right - left) > 1) {
            right = middle;
            continue;
        }
        else {
            return arr.size - (left + 1);
        }
    }

}



int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    arrey ar;
    int n;
    std::cout << "Введите точку отсчёта: ";
    std::cin >> n;
    int result = func(ar, n);
    std::cout << "Количество элементов в массиве больших, чем " << n << ":  " << result;
    return 0;
}

