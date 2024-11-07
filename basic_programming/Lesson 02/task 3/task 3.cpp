#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

struct adress {
    std::wstring sity;
    std::wstring street;
    int home;
    int apartment;
    int index;
};

void printAdress(adress& adr) {
    wcout << "Город: " << adr.sity << endl;
    wcout <<"Улица: "<< adr.street << endl;
    cout << "Дом: "<< adr.home << endl;
    cout << "Квартира: "<< adr.apartment << endl;
    cout << "Индекс: "<< adr.index << endl << endl;
}

int main() {
    //setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    adress first = { L"Москва", L"Арбат", 12, 8, 123456 };
    printAdress(first);

    adress second = { L"Ижевск", L"Пушкина", 59, 143, 953769 };
    printAdress(second);
}
