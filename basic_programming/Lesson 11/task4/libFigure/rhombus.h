#pragma once
#include "quadrangle.h"
#ifdef FIGURE_LIBRARYDYNAMIC_EXPORTS
#define FIGUR_API __declspec(dllexport)
#else
#define FIGUR_API __declspec(dllimport)
#endif

 class FIGUR_API rhombus : public quadrangle {
public:
    rhombus(int a, int A, int B);
};