#include <iostream>
#include <string>
#include <windows.h>



class figure {
protected:
    int sideCount;
    std::wstring name;
    int* side;
    int* corner;
    void basicPrint() {
        std::wcout << name;
        std::cout << std::endl;
        if (correct())  std::cout << "Правильная"; 
        else std::cout << "Неправильная";
        std::cout << std::endl << "Количество сторон: " << sideCount << std::endl;
    }
    int sumCorn() {
        int sum = 0;
        for (int i = 0; i < sideCount; i++) { sum = sum + corner[i]; }
        return sum;
    }
    void printEnd(int count) {
        std::cout << "Стороны: ";
        for (int i = 0; i < count; i++) {
            std::cout << char('a' + i) << "=" << side[i] << " ";
        }
        std::cout << std::endl << "Углы: ";
        for (int i = 0; i < count; i++) {
            std::cout << char('A' + i) << "=" << corner[i] << " ";
        }
        std::cout << std::endl << std::endl;
    }
public:
    figure() :sideCount(0), name(L"Фигура"), side(nullptr),corner(nullptr) {}
    figure(int Side, std::wstring nname) :sideCount(Side), name(nname) {
        if(Side>0){
            side = new int[Side];
            corner = new int[Side];
        }
    }
    virtual ~figure() {
        delete side;
        delete corner;
    }
    virtual void print() {
        basicPrint();
        std::cout << std::endl;
    }
    virtual bool correct() {
        if (sideCount == 0)return true;
        return false;
    }
};

class quadrangle : public figure {
protected:
    
    
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
    
    virtual bool correct() {
        if (sideCount==4 && sumCorn() == 360)return true;
        return false;
    }
    virtual void print() {
        basicPrint();
        printEnd(4);
    }
};


class triangle : public figure {
protected:
    
    
public:
    triangle(int a, int b, int c, int A, int B, int C) : triangle(a, b, c, A, B, C, L"Трёхугольник") {    }
    triangle(int a, int b, int c, int A, int B, int C, std::wstring nm) : figure(3, nm) {
        side[0] = a;
        side[1] = b;
        side[2] = c;
        corner[0] = A;
        corner[1] = B;
        corner[2] = C;
    }
    virtual bool correct() {
        if (sideCount==3 && sumCorn()==180) return true;
        return false;
    }
    virtual void print() {
        basicPrint();
        printEnd(3);
    }
    
};

class rightTriangle : public triangle { 
public:
    rightTriangle(int a, int b, int c, int A, int B, int C) : triangle(a, b, c, A, B, C, L"Прямоугольный треугольник") { }
    bool correct() override {
        if (triangle::correct() && corner[3] == 90)return true;
        return false;
    }
    void print() override {
        triangle::print();
    }
};

class isoscelesTriangle : public triangle {    
public:
    isoscelesTriangle(int a, int b, int c, int A, int B, int C) : triangle(a, b, c, A, B, C, L"Равнобедренный треугольник") { }
    bool correct() override {
        if (triangle::correct() && 
        side[0]==side[2] && corner[0]==corner[2])return true;
        return false;
    }
    void print() override {
        triangle::print();
    }
};

class equiLatTriangle : public triangle {    
public:
    equiLatTriangle(int a, int b, int c, int A, int B, int C) : triangle(a, b, c, A, B, C, L"Равносторонний треугольник") { }
    bool correct() override {
        int m = 0;
        for (int i = 0; i < 2; i++) {
            m = side[i] - side[i + 1];
            m = corner[i] - corner[i + 1];
        }
        if (triangle::correct() && m==0)return true;
        return false;
    }
    void print() override {
        triangle::print();
    }
};

class rectangle : public quadrangle {
public:
    rectangle(int a, int b, int c, int d, int A, int B, int C, int D) : quadrangle(a, b, c, d, A, B, C, D, L"Прямоугольник") {}
    bool correct() override {
        if (quadrangle::correct() && 
            corner[0] == corner[1] && corner[2] == corner[3] &&
            corner[1]==corner[2] && corner[0]==90 &&
            side[0]==side[2] && side[1]==side[3]
            )
            return true;
        return false;
    }
    void print() override {
        quadrangle::print();
    }
};

class square : public quadrangle {
public:
    square(int a, int b, int c, int d, int A, int B, int C, int D) : quadrangle(a, b, c, d, A, B, C, D, L"Квадрат") {}
    bool correct() override {
        int m = 0;
        for (int i = 0; i < 3; i++) {
            m = side[i] - side[i + 1];
            m = corner[i] - corner[i + 1];
        }
        if (quadrangle::correct() && m == 0)return true;
        return false;
    }
    void print() override {
        quadrangle::print();
    }
};

class parallelogram : public quadrangle {
public:
    parallelogram(int a, int b, int c, int d, int A, int B, int C, int D) : quadrangle(a, b, c, d, A, B, C, D, L"Параллелограмм") {}
    bool correct() override {
        if (quadrangle::correct() && side[0]==side[2] &&
        side[1]==side[3] && corner[0]==corner[2] &&
        corner[1]==corner[3]) return true;
        return false;
    }
    void print() override {
        quadrangle::print();
    }
};

class rhombus : public quadrangle {
public:
    rhombus(int a, int b, int c, int d, int A, int B, int C, int D) : quadrangle(a, b, c, d, A, B, C, D, L"Ромб") {}
    bool correct() override {
        if (quadrangle::correct()&& 
            side[0] == side[2] && side[0]==side[1] && side[0] == side[3]
            && corner[0] == corner[2] &&
            corner[1] == corner[3])return true;
        return false;
    }
    void print() override {
        quadrangle::print();
    }
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    figure* fig= new figure {  };
    fig->print();

    fig = new triangle { 10, 20, 30, 70, 50, 60 };
    fig->print();

    fig = new rightTriangle{ 10, 20, 30, 70, 50, 60 }; //Прямоугольный треугольник
    fig->print();

    fig = new isoscelesTriangle{ 10, 20, 10, 70, 40, 70 }; //Равнобедренный треугольник
    fig->print();

    fig = new equiLatTriangle{ 10, 10, 10, 60, 60, 60 }; //Равносторонний треугольник
    fig->print();

    fig = new quadrangle{ 10, 20, 30, 70, 50, 90, 70, 80 }; //Четырёхугольник
    fig->print();

    fig = new rectangle{ 10, 20, 10, 20, 90, 90, 90,90 }; //Прямоугольник
    fig->print();

    fig = new square{ 10, 10, 10, 10, 90, 90, 90, 90 }; //Квадрат
    fig->print();

    fig = new parallelogram{ 10, 20, 30, 70, 50, 60, 70,80 };
    fig->print();

    fig = new rhombus{ 80, 80, 80, 80, 80, 100, 80, 100};
    fig->print();

}