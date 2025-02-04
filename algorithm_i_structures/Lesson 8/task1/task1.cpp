#include <iostream>
#include "orgraph.h"




int main()
{
    setlocale(LC_ALL, "Russian");    
    Orgraph org ;
    org.fRead("input.txt");
    org.print();
    
}
