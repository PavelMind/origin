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
		std::cout << "������� ����� ������: ";
		std::cin >> num;
		if (num == 0) {
			std::cout << "�� ��������";
			return;
		}
		numSeas = static_cast<seasons>(num);
		switch (numSeas) {
		case seasons::January: std::cout << "������" << std::endl; break;
		  case seasons::February : std::cout << "�������" << std::endl; break;
		  case seasons::March: std::cout << "����" << std::endl; break;
		  case seasons::April : std::cout << "������" << std::endl; break;
		  case seasons::May: std::cout << "���" << std::endl; break;
		  case seasons::June: std::cout << "����" << std::endl; break;
		  case seasons::July: std::cout << "����" << std::endl; break;
		  case seasons::August: std::cout << "������" << std::endl; break;
		  case seasons::September: std::cout << "��������" << std::endl; break;
		  case seasons::October: std::cout  << "�������" << std::endl; break;
		  case seasons::November: std::cout << "������" << std::endl; break;
		  case seasons::December: std::cout  << "�������" << std::endl; break;
		  default: std::cout << "�� ���������� �����!"<<std::endl;
		}
	} 

}