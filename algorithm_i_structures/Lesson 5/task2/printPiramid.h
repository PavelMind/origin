#pragma once
#include <iostream>

void print_pyramid(int* arr, int size) {
    if (size > 0)
        std::cout << 0 << " - root : " << arr[0] << std::endl;
    int level = 0;
    bool ending = false;
    int countNextLvl = 1;
    do {

        int firstPerrent = pow(2, level) - 1;
        int countOnLvl = countNextLvl;
        countNextLvl = 0;
        for (int j = 0; j < countOnLvl; ++j) {
            int i = firstPerrent + j;
            if ((2 * i + 1) < size) {
                std::cout << level + 1 << " - left of (" << arr[i] << ") : " << arr[2 * i + 1] << std::endl;
                ++countNextLvl;
            }
            else ending = true;
            if ((2 * i + 2) < size) {
                std::cout << level + 1 << " - right of (" << arr[i] << ") : " << arr[2 * i + 2] << std::endl;
                ++countNextLvl;
            }
            else ending = true;
        }
        ++level;
    } while (!ending);

}