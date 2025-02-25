#include <iostream>
#include <vector>



class fuuunctor {
    int sum = 0;
    int count = 0;
public:
    fuuunctor() {}
    int get_sum() {
        return sum;
    }
    int get_count() {
        return count;
    }
    void operator () (int var){        
        if (var % 3 == 0) {
            sum += var;
            ++count;
        }
    }
};


int main()
{
    std::vector<int> vec{ 4, 1, 3, 6, 25, 54 };
    fuuunctor fu;
    std::cout << "[in]: ";
    for (auto i : vec) {
        std::cout << i << " ";
        fu(i);
    }
    
    std::cout << "\nget_sum() = " << fu.get_sum() <<
        "\nget_count() = " << fu.get_count();

}
