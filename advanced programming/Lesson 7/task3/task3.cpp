#include <iostream>
#include "vectory.hpp"







int main()
{
    try {
        my::vector<int> v1;
        std::cout << std::endl << "v1 size " << v1.size();
        std::cout << std::endl << "v1 capacity " << v1.capacity();
        //std::cout << std::endl << "v1 at[0] " << v1.at(0);// except

        my::vector<double> v2(5);
        v2.push_back(8);
        std::cout << std::endl << "v2 size " << v2.size();
        std::cout << std::endl << "v2 capacity " << v2.capacity();        
        std::cout << std::endl << "v2 at[0] " << v2.at(0);
#if 0
        my::vector<int> v3{ 2, 4, 7 };
        std::cout << std::endl << "v3 size " << v3.size();
        std::cout << std::endl << "v3 capacity " << v3.capacity();

        for (int i = 0; i < v3.size(); ++i) {
            std::cout << std::endl << "v3 at[" << i << "]: " << v3.at(i);
        }
        v3.push_back(8);
        v3.push_back(1);
        v3.push_back(26);

        for (int i = 0; i < v3.size(); ++i) {
            std::cout << std::endl << "v3 at[" << i << "]: " << v3.at(i);
        }
        //std::cout << v3.at(10);//except

#endif


    }
    catch (std::exception e) {
        std::cout << e.what();
    }
}