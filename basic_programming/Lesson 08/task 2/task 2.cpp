#include <iostream>
#include <string>
#include <windows.h>

#include "quadrangle.h"
#include "triangle.h"
#include "rightTriangle.h"
#include "isoscelesTriangle.h"
#include "equiLatTriangle.h"
#include "rectangle.h"
#include "square.h"
#include "parallelogram.h"
#include "rhombus.h"




int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
    try {
        triangle trng{ 10, 20, 30, 100, 70, 10 };

        rightTriangle rtrng{ 10, 20, 30, 20, 70, 90 };

        isoscelesTriangle ictrng{ 10, 20, 10, 30, 120, 30 };

        equiLatTriangle eqtrng{ 20, 20, 20, 60, 60,60 };

        quadrangle qdr{ 10, 20, 30, 40, 120, 60, 100, 80 };

        rectangle rect{ 10, 20, 10, 20, 90,90,90,90 };

        square sqr{ 30, 30, 30, 30, 90, 90, 90, 90 };

        parallelogram prllg{ 40, 50, 40, 50, 100, 80, 100, 80 };

        rhombus rmb{ 10, 10, 10, 10, 100, 80, 100, 80 };
    }
    catch (excFigure& ex) {
        std::cout<<"ошибка создания фигуры!!! Причина: "<<ex.what();
    }
    
}
