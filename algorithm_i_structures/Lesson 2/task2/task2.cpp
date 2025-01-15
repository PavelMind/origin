#include <iostream>
#include <vector>


int fiboRec(int a, int b, int n, int max, int* last) {  
    
    if (n == max) {
        (*last) = a;
        return b;        
    }
    else {
        int sum = a + b;
        //(*I) = n;
        return fiboRec(b, sum, ++n, max, last);
    }    
}


// 0  1  1  2  3  5  8  13  21



int searchMem(int max) {
    static std::vector<int> memory{-1};
    if (max > memory.size()) {
        memory.resize(max, -1);
    }
    int inMem1, inMem2;
    int i;
    int result;
    bool have = false;
    for (i = max - 1; i > 0; --i) {
            if (memory[i] != (-1) && memory[i-1]!=(-1)) {
                inMem2 = memory[i];
                inMem1 = memory[i - 1];                
                have = true;
                break;
            }            
    }
    
    //int I ;
    int last;
    if (have == false) {
        result = fiboRec(0, 1, 2, max, &last);        
    }
    else {
        result = fiboRec(inMem1, inMem2, i + 1, max, &last);
    }

    memory[max - 2] = last;
    memory[max-1] = result;    
    return result;  
}

int fibonachy(int max) {
    if (max == 1) return 0;
    if (max < 1) return -2;
    return searchMem(max);
}



int main()
{
    setlocale(LC_ALL, "Russian");
    int m;
    while (true) {
        std::cout << "Введите номер числа (или -1 для выхода): ";
        std::cin >> m;
        if (m == -1) break;
        int res = fibonachy(m);
        if (res == -2) {
            std::cout << "некорректное число!" << std::endl;
            continue;
        }
        std::cout << "Число Фибоначчи: " << res << std::endl;
    }
    return 0;
}
