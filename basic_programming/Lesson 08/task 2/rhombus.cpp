#include "rhombus.h"

rhombus::rhombus(int a, int b, int c, int d, int A, int B, int C, int D) : quadrangle(a, b, c, d, A, B, C, D, L"Ромб") {
	if (a != b || b != c || c != d) throw sideEqual();
	if (A != C || B != D) throw cornAC_and_BD();
	print();
}