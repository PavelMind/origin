#pragma once
#include "figure.h"

class triangle : public figure {

public:
    triangle(int a, int b, int c, int A, int B, int C);
    triangle(int a, int b, int c, int A, int B, int C, std::wstring nm);

};