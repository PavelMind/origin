#include <iostream>

enum class seasons {
	January=1,
	February,
	March,
	April,
	May,
	June,
	July,
	August,
	September,
	October,
	November,
	December
};


void main() {
	setlocale(LC_ALL, "Russian");
	int num;
	seasons numSeas;
	while (true) {
		std::cout << "Введите номер месяца: ";
		std::cin >> num;
		if (num == 0) {
			std::cout << "До свидания";
			return;
		}
		numSeas = static_cast<seasons>(num);
		switch (numSeas) {
		case seasons::January: std::cout << "Январь" << std::endl; break;
		  case seasons::February : std::cout << "Февраль" << std::endl; break;
		  case seasons::March: std::cout << "Март" << std::endl; break;
		  case seasons::April : std::cout << "Апрель" << std::endl; break;
		  case seasons::May: std::cout << "Май" << std::endl; break;
		  case seasons::June: std::cout << "Июнь" << std::endl; break;
		  case seasons::July: std::cout << "Июль" << std::endl; break;
		  case seasons::August: std::cout << "Август" << std::endl; break;
		  case seasons::September: std::cout << "Сентябрь" << std::endl; break;
		  case seasons::October: std::cout  << "Октябрь" << std::endl; break;
		  case seasons::November: std::cout << "Ноябрь" << std::endl; break;
		  case seasons::December: std::cout  << "Декабрь" << std::endl; break;
		  default: std::cout << "Не правильный номер!"<<std::endl;
		}
	} 

}