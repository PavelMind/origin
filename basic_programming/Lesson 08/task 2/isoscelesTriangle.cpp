#include "isoscelesTriangle.h"


isoscelesTriangle::isoscelesTriangle(int a, int b, int c, int A, int B, int C) :
	triangle(a, b, c, A, B, C, L"Равнобедренный треугольник") {
	if (a!=c) throw sideAC();
	if (A != C) throw cornAC();
	print();
}