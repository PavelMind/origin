#include "triangle.h"

triangle::triangle(int a, int b, int c, int A, int B, int C) : triangle(a, b, c, A, B, C, L"Трёхугольник") {    }
triangle::triangle(int a, int b, int c, int A, int B, int C, std::wstring nm) : figure(3, nm) {
    side[0] = a;
    side[1] = b;
    side[2] = c;
    corner[0] = A;
    corner[1] = B;
    corner[2] = C;
}