#include <iostream>

#include <set>


int main()
{
    int count;
    std::set<int> list;
    std::cout << "[IN] Count: ";
    std::cin >> count;
    int input;
    for (int i = 0; i < count; ++i) {        
        std::cin >> input;
        list.insert(input);
    }

    std::cout << "[OUT]" << std::endl;
    for (auto i = list.rbegin(); i != list.rend(); ++i) {
        std::cout << *i << std::endl;
    }
}
