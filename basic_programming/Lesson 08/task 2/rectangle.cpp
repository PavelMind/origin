#include "rectangle.h"



rectangle::rectangle(int a, int b, int c, int d, int A, int B, int C, int D) : quadrangle(a, b, c, d, A, B, C, D, L"Прямоугольник") {
	if (a!=c || b!=d) throw sideAC_and_BD();
	if (A!=90 || B!= 90 || C!= 90 || D!= 90) throw cornEqual90();
	print();
}