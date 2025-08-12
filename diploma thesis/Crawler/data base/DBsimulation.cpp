#include "DBsimulation.h"



void DBsimul::insertSite(sit r) {
    r.id = sites.size();
    sites.push_back(r);
}
void DBsimul::insertWord(wor r) {
    r.id = words.size();
    words.push_back(r);
}
void DBsimul::insertCount(int iS, int iW) {
    for (int i = 0; i < countes.size(); ++i) {
        if (countes[i].id_s == iS && countes[i].id_w == iW) {
            countes[i].count = countes[i].count + 1;
            return;
        }
            
    }
    counts cc{ iS, iW, 0 };
    countes.push_back(cc);
    
}

int DBsimul::selIDSite(const std::string& s) {
    for (int i = 0; i < sites.size(); ++i) {
        if (sites[i].URL == s)
            return sites[i].id;
    }
    return -1;
}
int DBsimul::selIDWord(const std::string& s) {
    for (int i = 0; i < words.size(); ++i) {
        if (words[i].word == s)
            return words[i].id;
    }
    return -1;
}
