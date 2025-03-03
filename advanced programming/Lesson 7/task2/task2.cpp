#include <iostream>

#include <set>
#include <vector>

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


    std::vector<int> result;
    for (auto i = list.rbegin() ; i != list.rend(); ++i) {
        result.push_back(*i);
    }

    std::cout << "[OUT]" << std::endl;    
    for (auto i : result) {
        std::cout << i << std::endl;
    }
}
