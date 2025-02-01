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
    int getN() { return N; }
    void fRead(std::string);
    void deepRound(int);
    void widthRound(int);
};