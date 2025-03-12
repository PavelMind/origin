#include <iostream>
#include <vector>
#include <string>

template<typename T>
void move_vectors(T& target, T&& source){
    target = std::move(source);
}

int main()
{
    std::vector <std::string> one = { "test_string1", "test_string2" };
    std::vector <std::string> two;
    move_vectors<std::vector <std::string>>(two, std::move(one));
    for (auto i : two) {
        std::cout << i << "\n";
    }
}
