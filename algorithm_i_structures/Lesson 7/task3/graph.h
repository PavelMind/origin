#pragma once
#include <string>
#include <vector>


class Graph {
    int** arr;
    int N;
    bool initialized;

    void alloc(int);
    void deepRoundRecurs(int, bool*);//для deepRound
    bool haveCycleRecurs(int, int, std::vector<bool>&);
public:
    Graph();    
    ~Graph();
    int getN() { return N; }
    void fRead(std::string);
    void deepRound(int);
    void widthRound(int);
    bool haveCycle();
};