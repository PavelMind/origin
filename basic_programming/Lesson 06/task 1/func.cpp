#include "func.h"
#include <iostream>
#include <math.h>

void sum(int a, int b) {
	std::cout << a << " ���� " << b << " = " << a + b;
}
void subtraction(int a, int b){
	std::cout << a << " ����� " << b << " = " << a - b;
}
void multiplication(int a, int b){
	std::cout << a << " �������� �� " << b << " = " << a * b;
}
void division(int a, int b){
	std::cout << a << " ������ �� " << b << " = " << a / b;
}
void power(int a, int b){
	std::cout << a << " � ������� " << b << " = " << pow(a , b);
}