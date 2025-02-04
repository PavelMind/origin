#include <iostream>
#include "orgraph.h"




int main()
{
    setlocale(LC_ALL, "Russian");
    Orgraph org;
    // input.txt    input2.txt
    org.fRead("input.txt");
    org.topologyRound();

}
