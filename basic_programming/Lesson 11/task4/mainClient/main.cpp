#include <iostream>
#include <string>

#include <windows.h>

#include "../libFigure/quadrangle.h"
#include "../libFigure/triangle.h"
#include "../libFigure/rightTriangle.h"
#include "../libFigure/isoscelesTriangle.h"
#include "../libFigure/equiLatTriangle.h"
#include "../libFigure/rectangle.h"
#include "../libFigure/square.h"
#include "../libFigure/parallelogram.h"
#include "../libFigure/rhombus.h"




int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    triangle trng{ 13,45,23,89,46,76 };
    trng.print();

    rightTriangle rtrng{ 23,66,75,34,23 };
    rtrng.print();

    isoscelesTriangle ictrng{ 23,66,89,67 };
    ictrng.print();

    equiLatTriangle eqtrng{ 28 };
    eqtrng.print();

    quadrangle qdr{ 23,55,6,44,7,8,99,60 };
    qdr.print();

    rectangle rect{ 20,11 };
    rect.print();

    square sqr{ 4 };
    sqr.print();

    parallelogram prllg{ 22,11, 43,56 };
    prllg.print();

    rhombus rmb{ 12,34,56 };
    rmb.print();
}
