#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

template<typename T>
void deleteOfDuplicate(std::vector<T>& vec) {
    std::set<T> haved;
    int endIndex = vec.size();

    for (int i = 0; i < endIndex; ) {
        if (std::find(haved.begin(), haved.end(), vec[i])
            == haved.end())
        {
            haved.insert(vec[i]);
            ++i;
        }
        else {
            vec[i] = vec[endIndex - 1];
            --endIndex;
        }
    }
    auto itForDelete = vec.begin();
    std::advance(itForDelete, endIndex);
    vec.erase(itForDelete, vec.end());
}
//  1, 1, 2, 5, 6, 1, 2, 4
//  1  4  2  5  6  1  2| 4
//  1  4  2  5  6  2| 2  4
//  1  4  2  5  6| 2  2  4

template<typename T>
void deleteOfDuplicate2(std::vector<T>& vec) {
    std::set<T> haved;
    int endIndex = vec.size();    

    for (int i = 0; i < endIndex; ) {
        if (std::find (haved.begin(), haved.end(), vec[i]) 
            == haved.end()) 
        {
            haved.insert(vec[i]);
            ++i;
        }
        else {
            auto itForDelete = vec.begin();
            std::advance(itForDelete, i);
            vec.erase(itForDelete);
            --endIndex;
        }
    }
}

int main()
{
    std::vector<int> vec{ 1, 1, 2, 5, 6, 1, 2, 4 };
    std::cout << "[IN]: ";
    for (auto i : vec) {
        std::cout << i << " ";
    }    
    
    auto vec_1(vec);
    deleteOfDuplicate(vec_1);
    std::cout << "\n[OUT 1]: ";
    for (auto i : vec_1) {
        std::cout << i << " ";
    }

    auto vec_2(vec);
    deleteOfDuplicate2(vec_2);
    std::cout << "\n[OUT 2]: ";
    for (auto i : vec_2) {
        std::cout << i << " ";
    }


}
