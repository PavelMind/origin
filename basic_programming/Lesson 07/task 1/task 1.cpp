#include <iostream>

#define MODE 1

#ifndef MODE
#error MODE не определена
#endif

#if MODE==1
int add(int a, int b) { return a + b; }
#endif 

int main()
{
    setlocale(LC_ALL, "Russian");
#if MODE==0
    std::cout << "Работаю в режиме тренировки";
#elif MODE==1
    int n1, n2;
    std::cout << "Работаю в боевом режиме\n";
    std::cout << "Введите число 1: ";
    std::cin >> n1;
    std::cout << "Введите число 2: ";
    std::cin >> n2;
    std::cout << "Результат сложения: " << add(n1, n2);
#else
    std::cout << "Неизвестный режим. Завершение работы";
#endif


}
