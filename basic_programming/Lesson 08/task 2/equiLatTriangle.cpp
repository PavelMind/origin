#include "equiLatTriangle.h"



equiLatTriangle::equiLatTriangle(int a, int b, int c, int A, int B, int C) :
	triangle(a, b, c, A, B, C, L"Равносторонний треугольник") {
	if (a!=b || a!=c) throw sideEqual();
	if (A!=60 || B!=60 || C!=60) throw cornEqual60();
	print();
}
