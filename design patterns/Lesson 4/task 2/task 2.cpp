#include <iostream>
#include <fstream>
#include "newVariant.h"


int main()
{
    std::ofstream file("filik.txt", std::ios::app);
    Data textForOut("Hello, good code");
    saveToAsHTML(file, &textForOut);
    saveToAsJSON(file, &textForOut);
    saveToAsText(file, &textForOut);
}
