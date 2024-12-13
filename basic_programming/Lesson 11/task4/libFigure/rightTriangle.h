#pragma once
#include "triangle.h"
#ifdef FIGURE_LIBRARYDYNAMIC_EXPORTS
#define FIGUR_API __declspec(dllexport)
#else
#define FIGUR_API __declspec(dllimport)
#endif

 class FIGUR_API rightTriangle : public triangle {  //прям треу
public:
    rightTriangle(int a, int b, int c, int A, int B);
};