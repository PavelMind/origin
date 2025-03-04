#include <iostream>
#include <set>
#include <list>
#include <vector>

template<typename Cont>
void print_container(Cont& cont) {
    for (auto i : cont) {
        std::cout << i <<" ";
    }
    std::cout << "\n\n";
}


int main()
{
    std::set<std::string> test_set = { "one", "two", "three", "four" };
    print_container(test_set);

    std::list<std::string> test_list = { "one", "two", "three", "four" };
    print_container(test_list);

    std::vector<std::string> test_vector = { "one", "two", "three", "four" };
    print_container(test_vector);
}
