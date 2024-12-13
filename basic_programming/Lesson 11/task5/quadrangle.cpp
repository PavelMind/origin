#include "quadrangle.h"



quadrangle::quadrangle(int a, int b, int c, int d, int A, int B, int C, int D) : quadrangle(a, b, c, d, A, B, C, D, L"Четырёхугольник") { }
quadrangle::quadrangle(int a, int b, int c, int d, int A, int B, int C, int D, std::wstring nm) : figure(4, nm) {
        side[0] = a;
        side[1] = b;
        side[2] = c;
        side[3] = d;
        corner[0] = A;
        corner[1] = B;
        corner[2] = C;
        corner[3] = D;
    }
