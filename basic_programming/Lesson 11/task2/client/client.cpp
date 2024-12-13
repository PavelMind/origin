#include <iostream>
#include <string>
#include "dunamo.h"
#include <windows.h>

int main() {
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::wstring name;
	dunamo::Leaver n;
	std::cout << "введите имя: ";
	std::wcin >> name;
	std::wcout << n.leave(name);

}