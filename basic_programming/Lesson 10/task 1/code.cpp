#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");

	std::string str;
	std::cout << "Введите имя: ";
	std::cin >> str;
	std::cout << "Здравствуйте, ";
	std::cout << str;
	return 0;
}
