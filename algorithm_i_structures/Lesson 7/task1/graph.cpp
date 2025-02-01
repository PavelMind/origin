#include "graph.h"
#include <iostream>
#include <fstream>


Graph::Graph() : arr(nullptr), initialized(false), N(0){}

Graph::~Graph() {
    if (initialized) {
        for (int i = 0; i < N; ++i) {
            delete arr[i];
        }
        delete[] arr;
    }
}

void Graph::alloc(int n) {
    if (!initialized) {
        arr = new int* [n];
        for (int i = 0; i < n; ++i) {
            arr[i] = new int[n];
        }
        initialized = true;
    }
    else {
        for (int i = 0; i < N; ++i) {
            delete arr[i];
        }
        delete[] arr;
        initialized = false;

        arr = new int* [n];
        for (int i = 0; i < n; ++i) {
            arr[i] = new int[n];
        }
        initialized = true;
    }
}

void Graph::fRead(std::string name){
    std::ifstream file(name);    
    file >> N;
    alloc(N);    
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            file >> arr[i][j];
        }
    }
    file.close();
}

void Graph::deepRound(int startVert) {
    bool* visited = new bool[N];
    for (int i = 0; i < N; ++i) {
        visited[i] = false;
    }
    deepRoundCycle(startVert, visited);
    delete[] visited;
}

void Graph::deepRoundCycle(int vert, bool* visited) {
    std::cout << vert << " ";
    visited[vert-1] = true;
    for (int i = 0; i < N; ++i) {
        if (arr[vert - 1][i] == 1 && visited[i] == false) {            
            deepRoundCycle(i+1, visited);
        }
    }
}





