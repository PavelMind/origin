#include <iostream>
#include "smart_array.h"


int main()
{
    smart_array arr(5);
    arr.add_element(1);
    arr.add_element(4);
    arr.add_element(155);

    int size = arr.size();
    std::cout << "arr:" << std::endl;
    for (int i = 0; i < size; ++i) {
        std::cout << arr.get_element(i) << std::endl;
    }

    smart_array new_array(2);
    new_array.add_element(44);
    new_array.add_element(34);

    arr = new_array;

    size = arr.size();
    std::cout << std::endl << "arr after = :" << std::endl;
    for (int i = 0; i < size; ++i) {
        std::cout << arr.get_element(i) << std::endl;
    }

    size = new_array.size();
    std::cout << std::endl << "new_array:" << std::endl;
    for (int i = 0; i < size; ++i) {
        std::cout << new_array.get_element(i) << std::endl;
    }


}
