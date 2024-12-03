#include "parallelogram.h"


parallelogram::parallelogram(int a, int b, int c, int d, int A, int B, int C, int D) :
	quadrangle(a, b, c, d, A, B, C, D, L"ֿאנאככוכמדנאלל") {
	if (A!=C || B!=D) throw cornAC_and_BD();
	if (a != c || b != d) throw sideAC_and_BD();
	print();
}