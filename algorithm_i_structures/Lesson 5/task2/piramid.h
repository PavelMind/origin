#pragma once
#include <iostream>
#include "support.h"

class piramid {
    int index;
    int i_perrent;
    int level;
    
    int* arr;
    int size;

    result commandUp(){
        if (i_perrent == -1) 
            throw badUp{};
        index = i_perrent;
        --level;
        if (level == 0)
            i_perrent = -1;
        else if (index % 2 == 0)
            i_perrent = (index - 2) / 2;
        else
            i_perrent = (index - 1) / 2;
       
        return ok;
    }
    result commandLeft() {
        int temp = 2 * index + 1;
        if (temp < size) {
            i_perrent = index;
            index = temp;
            ++level;
        }
        else throw badLeft{};
        return ok;
    }
    result commandRight() {
        int temp = 2 * index + 2;
        if (temp < size) {
            i_perrent = index;
            index = temp;
            ++level;
        }
        else throw badLeft{};
        return ok;
    }
    result commandExit() {
        return Exit;
    }

    
public:
    piramid(int* ARR, int SZ) : index(0), i_perrent(-1), level(0), arr(ARR), size(SZ) { }
    result input(std::string in) {
        if (in == "up") {
            return commandUp();
        }
        else if (in == "left") {
            return commandLeft();
        }
        else if (in == "right") {
            return commandRight();
        }
        else if (in == "exit") {
            return commandExit();
        }
        else {
            throw badInput{};
        }
    }
    void print() {
        std::cout << "Вы находитесь здесь: ";
        if (i_perrent == -1)
            std::cout << level << " root : " << arr[index] << std::endl;
        else {
            std::cout << level << " ";
            if (index % 2 == 0)
                std::cout << "right";
            else
                std::cout << "left";
            std::cout << " of(" << arr[i_perrent] << ") : " << arr[index] << std::endl;
        }
    }
};