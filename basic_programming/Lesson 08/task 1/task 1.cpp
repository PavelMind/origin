#include <iostream>
#include <string>
#include <windows.h>

class bad_length {
public:
    const char* what(){ return "Вы ввели слово запретной длины! До свидания"; }
};

int function(std::wstring str, int forbidden_length) {
    if (str.length() == forbidden_length) {
        throw bad_length();
    }
    else return str.length();
}

int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int length, maxLength;
    std::wstring str;
    std::cout << "Введите запретную длину: ";
    std::cin >> maxLength;
    do {
        std::cout << "Введите слово: ";
        std::wcin >> str;
        try{
            length = function(str, maxLength);
            std::cout << "длина слова ";
            std::wcout << str;
            std::cout << " равна " << length<<std::endl;
        }
        catch(bad_length ex){
            std::cout << ex.what();
            return 0;
        }
    } while (true);
}
