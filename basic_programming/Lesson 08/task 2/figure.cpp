#include "figure.h"


figure::figure() :sideCount(0), name(L"Фигура"), side(nullptr), corner(nullptr) {}
figure::figure(int Side, std::wstring nname) :sideCount(Side), name(nname) {
    side = new int[Side];
    corner = new int[Side];
}
figure::~figure() {
    delete side;
    delete corner;
}
void figure::print() {
    std::wcout << name;
    std::cout << " (Стороны: ";
    for (int i = 0; i < sideCount; i++) {
        std::cout << char('a' + i) << "=" << side[i] << " ";
    }
    std::cout << "; Углы: ";
    for (int i = 0; i < sideCount; i++) {
        std::cout << char('A' + i) << "=" << corner[i] << " ";
    }
    std::cout << ") создан !!!" << std::endl << std::endl;
}



