#include <iostream>
#include <string>

int simple_string_hash(std::string str) {
    
    int sum = 0;
    for (int i : str) {
        sum += i;
    }
    return sum;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    std::string str;
    do {
        std::cout << "Введите строку: ";
        std::cin >> str;
        int hash = simple_string_hash(str);
        std::cout << "Хеш строки "<<str<<" : " << hash << std::endl;
    } while (str != "exit");
}
