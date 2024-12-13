#pragma once
#include "quadrangle.h"
#ifdef FIGURE_LIBRARYDYNAMIC_EXPORTS
#define FIGUR_API __declspec(dllexport)
#else
#define FIGUR_API __declspec(dllimport)
#endif

class FIGUR_API parallelogram : public quadrangle {
public:
    parallelogram(int a, int b, int A, int B);
};