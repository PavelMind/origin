#include <iostream>
#include <string>

class figure {
    int sadeCount;
    std::wstring name;
public:
    figure() :sadeCount(0), name( L"Фигура" ) {}
    figure(int sade, std::wstring nname) :sadeCount(sade),name(nname) {}
    
    void print() {
        std::wcout << name << ": " << sadeCount << std::endl;
    }
};

class rectange: public figure {
public: 
    rectange() : figure(4,  L"Четырёхугольник" ) {}
};

class triangle: public figure {
public:
    triangle() : figure(3, L"Трёхугольник") {}
};


int main()
{
    setlocale(LC_ALL, "Russian");
    std::cout << "Колличество сторон:\n";
    figure fig;
    fig.print();
    triangle trng;
    trng.print();
    rectange rect;
    rect.print();
}
