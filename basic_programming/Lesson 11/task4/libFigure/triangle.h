#pragma once
#include "figure.h"
#ifdef FIGURE_LIBRARYDYNAMIC_EXPORTS
#define FIGUR_API __declspec(dllexport)
#else
#define FIGUR_API __declspec(dllimport)
#endif
 class FIGUR_API triangle : public figure {

public:
    triangle(int a, int b, int c, int A, int B, int C);
    triangle(int a, int b, int c, int A, int B, int C, std::wstring nm);

};