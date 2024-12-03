#include "figure.h"


figure::figure() :sideCount(0), name(L"������"), side(nullptr), corner(nullptr) {}
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
    std::cout << " (�������: ";
    for (int i = 0; i < sideCount; i++) {
        std::cout << char('a' + i) << "=" << side[i] << " ";
    }
    std::cout << "; ����: ";
    for (int i = 0; i < sideCount; i++) {
        std::cout << char('A' + i) << "=" << corner[i] << " ";
    }
    std::cout << ") ������ !!!" << std::endl << std::endl;
}



