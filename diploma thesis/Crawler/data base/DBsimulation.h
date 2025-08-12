#pragma once
#include <vector>
#include <string>
#include <utility>
//using namespace std;

struct counts {
    int id_s;
    int id_w;
    int count;
};
struct sit {
    int id;
    std::string title;
    std::string URL;
};
struct wor {
    int id;
    std::string word;

};


class DBsimul {
public:
    
    std::vector<sit> sites;
    std::vector<wor> words;
    std::vector<counts> countes;

    DBsimul() {}
    void insertSite(sit);
    void insertWord(wor);
    void insertCount(int, int);

    int selIDSite(const std::string&);
    int selIDWord(const std::string&);
    //int selIDCount(int, int);
};