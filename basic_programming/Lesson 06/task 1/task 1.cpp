#include <iostream>
#include "func.h"

int main()
{
    setlocale(LC_ALL, "Russian");
    int in, num1, num2;
    std::cout << "Введите первое число: ";
    std::cin >> num1;
    std::cout << "Введите второе число: ";
    std::cin >> num2;
    std::cout << "Выберите операцию (1 - сложение, 2 вычитание, 3 - умножение, 4 - деление, 5 - возведение в степень): ";
    std::cin >> in;
    switch (in)
    {
    case 1: sum(num1, num2); break;
    case 2: subtraction(num1, num2); break;
    case 3: multiplication(num1, num2); break;
    case 4: division(num1, num2); break;
    case 5: power(num1, num2); break;
    default:
        break;
    }

}
