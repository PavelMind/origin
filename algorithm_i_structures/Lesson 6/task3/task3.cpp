#include <iostream>
#include <string>


int simple_string_hash(std::string str) {
    int sum = 0;
    for (int i : str) {
        sum += i;
    }
    return sum;
}

int find_substring_light_rabin_karp(std::string& mainStr, std::string& soughtStr) {
    int soughtHash = simple_string_hash(soughtStr);
    int length = soughtStr.length();
    if (length > mainStr.length())
        return -1;
    auto begIt = mainStr.begin();
    auto startIt = begIt;
    auto endIt = begIt + length - 1;
    std::string subStr{ begIt, endIt +1 };
    int iterHash = simple_string_hash(subStr);

    int countIter = mainStr.length() - length;
    for (int i = 0; i < countIter + 1; ++i) {
        if (iterHash == soughtHash) {
            auto mainIt = begIt;
            auto soughtIt = soughtStr.begin();
            bool isHave = true;
            for (int j = 0; j < length; ++j) {                
                if (*mainIt == *soughtIt) {
                    ++mainIt;
                    ++soughtIt;
                }
                else {
                    isHave = false;
                    break;
                }
                
            }
            if (isHave) {
                return begIt - startIt;
            }
        }
        if (i < countIter) {
            ++endIt;            
            iterHash = iterHash - (static_cast<int>(*begIt));
            ++begIt;            
            iterHash = iterHash + (static_cast<int>(*endIt));
        }

    }
return -2;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    std::string strMain, strSought;
    std::cout << "Введите строку, в которой надо искать: ";
    std::cin >> strMain;
    do {        
        std::cout << "Введите строку, которую нужно найти: ";
        std::cin >> strSought;
        int result = find_substring_light_rabin_karp(strMain, strSought);
        if (result == -1) {
            std::cout << "Искомая строка больше, чем та, в которой её надо найти!"<<std::endl;
            continue;
        }
        if (result == -2) {
            std::cout << "Строка не найдена." << std::endl;
            continue;
        }
        std::cout << "Подстрока "<< strSought <<" найдена на индексе " << result << std::endl;
    } while (strSought != "exit");

}

