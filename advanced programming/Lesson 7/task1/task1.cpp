#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <utility>



class less {
    using type = std::pair<char, int>;
public:
    bool operator ()(type a, type b) {
        return a.second < b.second;
    }
};

auto sort(std::string& str) {
    std::map<char, int> mapy;
    using type = std::pair<char, int>;
    std::priority_queue<type, std::vector<type>, less > queue;

    for (auto i : str) {
        if (mapy.find(i) == mapy.end()) {
            mapy[i] = 1;
        }
        else {
            auto tmp = mapy[i];
            mapy[i] = ++tmp;
        }
    }

    for (auto i : mapy) {
        std::pair<char, int> tmp(i.first, i.second);        
        queue.push(tmp);
    }

    return queue;
}





int main()
{
    std::string str{ "Hello World!!" };
    std::cout << str << "\n";
    auto result = sort(str);
    while (result.size() != 0) {
        auto tmp = result.top();
        std::cout << tmp.first << ": " << tmp.second << std::endl;
        result.pop();
    }
    
}
