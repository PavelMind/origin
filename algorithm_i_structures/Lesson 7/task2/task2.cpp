#include <iostream>
#include "graph.h"



int main()
{
    setlocale(LC_ALL, "Russian");
    Graph graph;
    graph.fRead("input.txt");
    std::cout << "Вершин в графе " << graph.getN() << ". Введите номер вершины, с которой начнётся обход: ";
    int start;
    std::cin >> start;
    std::cout << "Порядок обхода вершин: ";
    graph.widthRound(start-1);
}
