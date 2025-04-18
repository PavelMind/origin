#include "orgraph.h"
#include <fstream>
#include <iostream>



Orgraph::Orgraph() :   N(0) {}

Orgraph::~Orgraph() { }

void Orgraph::alloc(int n) {
    arr.resize(n);
    for (int i = 0; i < n; ++i) {
        arr[i].resize(n);
    }    
}

void Orgraph::fRead(std::string name) {
    std::ifstream file(name);
    file >> N;
    alloc(N);
    int temp;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            file >> temp;
            arr[i][j] = static_cast<bool>(temp);
        }
    }
    file.close();
}

void Orgraph::print() {
    std::cout << "��������� ��� �������" << std::endl;
    for (int i = 0; i < N; ++i) {
        std::cout << i + 1 << ": ";
        bool have = false;
        for (int j = 0; j < N; ++j) {
            if (arr[i][j] == true) {
                have = true;
                std::cout << j + 1 << " ";
            }            
        }
        if (!have)
            std::cout << "���";
        std::cout << std::endl;
    }   
}






