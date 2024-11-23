#include <iostream>
#include <string>
#include <windows.h>


class figure {
protected:
    int sideCount;
    std::wstring name;
    int* side;
    int* corner;
public:
    figure() :sideCount(0), name(L"Фигура") {}
    figure(int Side, std::wstring nname) :sideCount(Side), name(nname) {
        side = new int[Side];
        corner = new int[Side];
    }
    ~figure() {
        delete side;
        delete corner;
    }
    void print() {
        std::wcout << name;
        std::cout<< ": " << std::endl << "Стороны: ";
        for (int i = 0; i < sideCount; i++) {
            std::cout << char('a'+i) << "=" << side[i] << " ";
        }
        std::cout << std::endl << "Углы: ";
        for (int i = 0; i < sideCount; i++) {
            std::cout << char('A'+i) << "=" << corner[i] << " ";
        }
        std::cout << std::endl << std::endl;
    }
    
};

class quadrangle : public figure {
    
public:
    quadrangle(int a, int b, int c, int d, int A, int B, int C, int D) : quadrangle(a, b, c, d, A, B, C, D, L"Четырёхугольник") { }
    quadrangle(int a, int b, int c, int d, int A, int B, int C, int D, std::wstring nm) : figure(4, nm) {
        side[0] = a;
        side[1] = b;
        side[2] = c;
        side[3] = d;
        corner[0] = A;
        corner[1] = B;
        corner[2] = C;
        corner[3] = D;       
    }
    
};

class triangle : public figure {
    
public:
    triangle(int a, int b, int c, int A, int B, int C) : triangle(a,b,c,A,B,C, L"Трёхугольник") {    }
    triangle(int a, int b, int c, int A, int B, int C, std::wstring nm) : figure(3, nm) {
        side[0] = a;
        side[1] = b;
        side[2] = c;
        corner[0] = A;
        corner[1] = B;
        corner[2] = C;
    }
    
};

class rightTriangle: public triangle {  //прям треу
public:
    rightTriangle(int a, int b, int c, int A, int B): triangle(a,b,c,A,B,90, L"Прямоугольный треугольник") { }
};

class isoscelesTriangle : public triangle {     //равнобедр
public:
    isoscelesTriangle(int a, int b, int A, int B): triangle(a, b, a, A, B, A, L"Равнобедренный треугольник") { }
};

class equiLatTriangle: public triangle {    //равносторон
public:
    equiLatTriangle(int a) : triangle(a, a, a, 60, 60, 60, L"Равносторонний треугольник") { }
}; 

class rectangle: public quadrangle {
public:
    rectangle(int a, int b) : quadrangle(a, b, a, b, 90, 90, 90, 90, L"Прямоугольник"){}
};

class square: public quadrangle {
public:
    square(int a) : quadrangle(a, a, a, a, 90, 90, 90, 90, L"Квадрат") {}
};//квадр

class parallelogram: public quadrangle {
public:
    parallelogram(int a, int b, int A, int B) : quadrangle(a, b, a, b, A, B, A, B, L"Параллелограмм") {}
};

class rhombus: public quadrangle {
public:
    rhombus(int a, int A, int B) : quadrangle(a, a, a, a, A, B, A, B, L"Ромб") {}
};

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
