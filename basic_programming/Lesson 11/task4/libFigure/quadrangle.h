#pragma once
#include "figure.h"
#ifdef FIGURE_LIBRARYDYNAMIC_EXPORTS
#define FIGUR_API __declspec(dllexport)
#else
#define FIGUR_API __declspec(dllimport)
#endif

 class FIGUR_API quadrangle : public figure {

public:
    quadrangle(int a, int b, int c, int d, int A, int B, int C, int D);
    quadrangle(int a, int b, int c, int d, int A, int B, int C, int D, std::wstring nm);

};