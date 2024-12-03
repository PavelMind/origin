#include "square.h"


square::square(int a, int b, int c, int d, int A, int B, int C, int D) : quadrangle(a, b, c, d, A, B, C, D, L" вадрат") {
	if (A != 90 || B != 90 || C != 90 || D!=90) throw cornEqual90();
	if (a != b || b != c || c != d) throw sideEqual();
	print();
}