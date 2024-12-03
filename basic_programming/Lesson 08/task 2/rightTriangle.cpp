#include "rightTriangle.h"

rightTriangle::rightTriangle(int a, int b, int c, int A, int B, int C) : triangle(a, b, c, A, B, C, L"Прямоугольный треугольник") { 
	if (C!=90) throw reghtTriangle();
	print();
}