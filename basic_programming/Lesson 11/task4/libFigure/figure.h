#pragma once
#include <iostream>
#include <string>
#ifdef FIGURE_LIBRARYDYNAMIC_EXPORTS
#define FIGUR_API __declspec(dllexport)
#else
#define FIGUR_API __declspec(dllimport)
#endif

 class FIGUR_API figure {
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