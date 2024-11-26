#include "func.h"
#include <iostream>
#include <math.h>

void sum(int a, int b) {
	std::cout << a << " плюс " << b << " = " << a + b;
}
void subtraction(int a, int b){
	std::cout << a << " минус " << b << " = " << a - b;
}
void multiplication(int a, int b){
	std::cout << a << " умножить на " << b << " = " << a * b;
}
void division(int a, int b){
	std::cout << a << " делить на " << b << " = " << a / b;
}
void power(int a, int b){
	std::cout << a << " в степени " << b << " = " << pow(a , b);
}