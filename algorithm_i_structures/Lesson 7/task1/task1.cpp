#include <iostream>
#include "graph.h"



int main()
{
    setlocale(LC_ALL, "Russian");
    Graph graph;
    graph.fRead("input.txt");
    std::cout << "Порядок обхода вершин: ";
    graph.deepRound(1);
}
