#include <iostream>
#include <string>
#include <windows.h>

class Counter {
    int count;
public:
    Counter() : count(1) { }
    Counter(int co): count(co) { }
    void print() { std::cout << count <<std::endl; }
    void increm() {
        count++;
    }
    void decrem() {
        count--;
    }

};


  int main() 
  {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::wstring isInit;
    int init;
    std::cout << "Вы хотите указать начальное значение счётчика? Введите да или нет: ";
    std::wcin >> isInit;
    Counter* count;
    if (isInit == L"да") {
        std::cout << "Введите начальное значение счётчика: ";
        std::cin >> init;
        count= new Counter(init) ;
    }
    else { count = new Counter (); }


    char input;
    while (true) {
        std::cout << "Введите команду('+', '-', '=' или 'x') : ";
        std::cin >> input;
        switch (input) {
        case '+': count->increm(); break;
        case '-': count->decrem(); break;
        case '=': count->print(); break;
        case 'x': std::cout << "До свидания!"; return 0; // x латиницей(x english)
        default: std::cout << "неверный символ";
        }
    }
    delete count;
    return 0;
  }
