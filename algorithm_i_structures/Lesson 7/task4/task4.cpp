#include <iostream>
#include <vector>
#include "graph.h"


int main()
{
    setlocale(LC_ALL, "Russian");
    Graph graph;
    // input.txt    input2.txt
    graph.fRead("input.txt");
    std::vector<int> result;    
    int count = graph.connectComponents(result);
    int N = result.size();
    std::cout << "Принадлежность вершин компонентам связности: " << std::endl;
    for (int i = 0; i < N; ++i) {
        std::cout << i + 1 << " в " << result[i] << std::endl;
    }
    std::cout << "Всего компонент связности в графе: " << count;
    
}