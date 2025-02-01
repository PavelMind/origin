#include <iostream>
#include "graph.h"


int main()
{
    setlocale(LC_ALL, "Russian");
    Graph graph;
    // input.txt    input2.txt  input3.txt
    graph.fRead("input.txt");
    if (graph.haveCycle()) {
        std::cout << "В графе цикл есть!";
    }
    else
        std::cout << "В графе нет циклов.";    
}
/* input3.txt

    1       4--6        3
    |       | /
    2       |/
            5------7

*/
