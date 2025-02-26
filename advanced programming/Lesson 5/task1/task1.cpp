#include <iostream>
#include <vector>

template<typename T>
void square(T& var) {
    var = var * var;
}

template<typename T>
void square(std::vector<T>& var) {
    for (int i = 0; i < var.size(); ++i) {
        var[i] = var[i] * var[i];
    }
    
}

int main()
{
    int varI = 4;
    std::cout << "[in]: " << varI << std::endl;
    square(varI);
    std::cout << "[out]: " << varI << std::endl << std::endl;

    std::vector<int> vec{-1, 4, 8};
    std::cout << "[in]: ";
    for (auto i : vec) {
        std::cout << i <<", ";

    }
    std::cout << std::endl;
    square(vec);
    std::cout << "[out]: ";
    for (auto i : vec) {
        std::cout << i << ", ";
    }

    
}
