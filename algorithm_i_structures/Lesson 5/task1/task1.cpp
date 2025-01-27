#include <iostream>
#include <cmath>

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
/*
------------------------------------
2|4 3|5 6 4 7|6 7 7  8  5  5  8
0 1 2 3 4 5 6 7 8 9 10 11 12 13

                2
            4       3
    5       6       4        7
6   7    7  8       5  5     8  

*/


int main()
{
    setlocale(LC_ALL, "Russian");
    //int const SIZE = 14;
    //int piramid[SIZE]{ 2, 4, 3, 5, 6, 4, 7, 6, 7, 7,  8,  5,  5,  8 };
    int const SIZE = 10;
    int piramid[SIZE]{ 16, 11, 9, 10, 5, 6, 8, 1, 2, 4 };

    if (SIZE < 1) return 0;
    std::cout << "Массив пирамиды: ";
    for (int i : piramid) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    print_pyramid(piramid, SIZE);
    return 0;
}
