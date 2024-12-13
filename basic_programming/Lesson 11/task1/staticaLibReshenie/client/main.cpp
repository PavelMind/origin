#include <iostream>
#include <string>
#include "greeter.h"
#include "windows.h"

int main() {
	
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");
	std::wstring name;
	spaceGr::Greeter g;
	std::cout << "введите имя: ";
	std::wcin >> name;
	std::wcout << g.greet(name);

}