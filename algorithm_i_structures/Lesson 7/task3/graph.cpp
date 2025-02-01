#include "graph.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>


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
    deepRoundRecurs(startVert, visited);
    delete[] visited;
}

void Graph::deepRoundRecurs(int vert, bool* visited) {
    std::cout << vert+1 << " ";
    visited[vert] = true;
    for (int i = 0; i < N; ++i) {
        if (arr[vert][i] == 1 && visited[i] == false) {            
            deepRoundRecurs(i, visited);
        }
    }
}

void Graph::widthRound(int startVert) {
    std::vector<bool> visited(N, false);
    std::queue<int> queueV;     //pop - delete first(front)
    queueV.push(startVert);
    visited[startVert] = true;

    while (!queueV.empty()) {
        int vert = queueV.front();
        std::cout << vert + 1 << " ";
        queueV.pop();        

        for (int i = 0; i < N; ++i) {
            if (arr[vert][i] == 1 && visited[i] == false) {
                queueV.push(i);
                visited[i] = true;
            }
        }
    }

}

bool Graph::haveCycle() {
    std::vector<bool> visited(N, false);
    bool have = false;
    for (int n = 0; n < N; ++n) {
        if (visited[n] == false) {
            visited[n] = true;

            for (int i = 0; i < N; ++i) {
                if (arr[n][i] == 1 && visited[i] == false) {
                    have = haveCycleRecurs(i, n, visited);
                    if (have) return true;
                }
            }

        }//if

    }
    return false;
}

bool Graph::haveCycleRecurs(int vert, int last, std::vector<bool>& visited) {    
    visited[vert] = true;
    for (int i = 0; i < N; ++i) {

        if (arr[vert][i] == 1  &&  i != last ) {
            if (visited[i] == false) {
                bool have = false;
                have = haveCycleRecurs(i, vert, visited);
                if (have) return true;
            }
            else return true;
        }
    }
    return false;
}

