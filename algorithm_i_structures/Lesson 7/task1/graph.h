#pragma once
#include <string>

class Graph {
    int** arr;
    int N;
    bool initialized;

    void alloc(int);
    void deepRoundCycle(int, bool*);
public:
    Graph();    
    ~Graph();
    void fRead(std::string);
    void deepRound(int);
};