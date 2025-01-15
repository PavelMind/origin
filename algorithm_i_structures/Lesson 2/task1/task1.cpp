#include <iostream>



int fiboRec(int a, int b, int n, int max) {    
    
    if (n == max) {
        return b;
    }
    else {
        int sum = a + b;
        return fiboRec(b, sum, ++n, max);
    }
    

}

int fibonachy(int max) {
    if (max == 1) return 0;
    if (max < 1) return -1;
    return fiboRec(0, 1, 2, max);
}

// 0  1  1  2  3  5  8  13  21


int main()
{
    setlocale(LC_ALL, "Russian");
    int m;
    std::cout << "Введите номер числа: ";
    std::cin >> m;
    int res = fibonachy(m);
    std::cout << "Число Фибоначчи: " << res << std::endl;
    return 0;
}
