#include <iostream>
#include <string>
#include <windows.h>

struct bankSchot {
    int number;
    std::wstring name;
    double money;
};

void editSchot(bankSchot& bs, int newM) {
    bs.money = newM;
}

int main()
{
    //setlocale(LC_ALL, "Russian"); не помогал, wcout<<schot.name; всё равно давал мусор
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    bankSchot schot;
    std::cout << "Введите номер счёта : ";
    std::cin >> schot.number;
    std::cout << "Введите имя: ";
    std::wcin >> schot.name;
    std::cout << "Введите баланс: ";
    std::cin >> schot.money;

    int nowMoney;
    std::cout << "Введите новый баланс : ";
    std::cin >> nowMoney;
    editSchot(schot, nowMoney);
    std::cout << "Ваш счёт: ";
    std::wcout << schot.name;
    std::cout.setf(std::ios::fixed); //  почему-то обнуляет всё после точки
    std::cout.precision(2);
    std::cout << ", " << schot.number << ", " << schot.money;
}
