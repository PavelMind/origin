#include <iostream>
#include <windows.h>
#include "printPiramid.h"
#include "support.h"
#include "piramid.h"


/*
------------------------------------
2|4 3|5 6 4 7|6 7 7  8  5  5  8
0 1 2 3 4 5 6 7 8 9 10 11 12 13

                2
            4       3
    5       6       4        7
6   7    7  8       5  5     8
*/





int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int const SIZE = 14;
    int arr[SIZE]{ 2, 4, 3, 5, 6, 4, 7, 6, 7, 7,  8,  5,  5,  8 };
    //int const SIZE = 10;
    //int arr[SIZE]{ 16, 11, 9, 10, 5, 6, 8, 1, 2, 4 };

    if (SIZE < 1) return 0;
    std::cout << "Массив пирамиды: ";
    for (int i : arr) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    print_pyramid(arr, SIZE);
    std::cout << std::endl;
    piramid target{ arr, SIZE };
    target.print();
    do{
        try
        {
            std::string in;
            std::cout << "Введите комманду(up, left, right, exit): ";
            std::cin >> in;
            result res;
            res = target.input(in);
            if ( res == Exit)
                break;
            if (res == ok)
                std::cout << "ОК. "<<std::endl;
            target.print();
        }        
        catch (badCommand& c)
        {
            std::wcout << c.what();
            std::cout << std::endl;
        }
    } while (true);
    return 0;
}