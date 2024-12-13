#pragma once
#include "triangle.h"

#ifdef FIGURE_LIBRARYDYNAMIC_EXPORTS
#define FIGUR_API __declspec(dllexport)
#else
#define FIGUR_API __declspec(dllimport)
#endif

 class FIGUR_API equiLatTriangle : public triangle {    //равносторон
public:
    equiLatTriangle(int a);
};