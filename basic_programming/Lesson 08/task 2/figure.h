#pragma once
#include <iostream>
#include <string>
#include "exception.h"

class figure {
protected:
    int sideCount;
    std::wstring name;
    int* side;
    int* corner;
public:
    figure();
    figure(int Side, std::wstring nname);
    ~figure();
    void print();

};