#include <iostream>
#include <string>
#include "vectory.hpp"


template<typename T>
void print(my::vector<T>& vec, std::string name) {
    std::cout << name << "\nsize " << vec.size();
    std::cout << "\ncapacity " << vec.capacity();
    int sz = vec.size();
    for (int i = 0; i < sz; ++i) {
        std::cout << std::endl << " [" << i << "]: " << vec.at(i);
    }
    std::cout << "\n\n";
}


int main()
{
    try {
        my::vector<int> v1;
        std::cout << "v1 size " << v1.size();
        std::cout << std::endl << "v1 capacity " << v1.capacity();
        //std::cout << std::endl << "v1 at[0] " << v1.at(0);// except

        std::cout << std::endl << std::endl;
        my::vector<double> v2(5);
        v2.push_back(2);
        v2.push_back(4);
        v2.push_back(6);
        v2.push_back(8);
        v2.push_back(10);                
        std::cout << "v2 at[0] " << v2.at(0) <<"\n";
        print<>(v2, "v2");

        my::vector<double> v3(4);
        v3.push_back(1);
        v3.push_back(3);
        v3.push_back(5);        
        print<double>(v3, "v3");

        my::vector<double> v4(v3);          
        print<double>(v4, "v4   (v3)");

        v3 = v2;
        std::cout << "v3=v2\n";        
        print<double>(v3, "v3");

        v2 = v4;
        std::cout << "v2 = v4\n";
        print<double>(v2, "v2");
        
#if 1
        my::vector<int> v5{ 2, 4, 7 };
        print<>(v5, "v5");
        v5.push_back(8);
        v5.push_back(1);
        v5.push_back(26);

        print<>(v5, "v5");
        
        //std::cout << "v6";  my::vector<short> v6(0);//exept
#endif

    }
    catch (std::exception e) {
        std::cout << e.what();
    }
}