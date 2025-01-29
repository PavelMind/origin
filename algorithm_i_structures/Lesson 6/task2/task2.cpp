#include <iostream>
#include <string>
#include <cmath>
#include <stdint.h>


long long real_string_hash(std::string str, int p, int n) {

    unsigned long long sum = 0;
    int step = 0;
    for (int i = 0 ; i < str.length(); ++i, ++step) {
        unsigned int po =pow(p, step);
        sum += str[i] * po;
        
    }
    return sum % n;
}

long long reality_real_string_hash(std::string str, int p, int n) {

    unsigned long long sum = 0;
    int step = 0;
    for (int i = 0; i < str.length(); ++i, ++step) {
        unsigned long long po = pow(p, step);
        sum += str[i] * po;
        
    }
    return sum % n;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    int p, n;
    std::string str;
    std::cout << "Введите p: ";
    std::cin >> p;
    std::cout << "Введите n: ";
    std::cin >> n;
    do {        
        std::cout << "Введите строку: ";
        std::cin >> str;
        unsigned long long hash = real_string_hash(str, p, n);
        unsigned long long hash2 = reality_real_string_hash(str, p, n);
        std::cout << "Хеш строки " << str << " : " << hash2 <<"; с обрезанием по int: "<<hash << std::endl;
    } while (str != "exit");

}
