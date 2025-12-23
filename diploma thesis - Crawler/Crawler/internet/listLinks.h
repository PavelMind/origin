#pragma once
#include <mutex>
#include <set>
#include <vector>
#include "addrSite.h"

class listLinks {
    std::mutex mutP, mutL;
    std::set<addrSite> processed;
    std::vector<addrSite> links;
public:
    std::vector<addrSite>&& getLinks();
    void push(addrSite&);
    bool isProcAndMarked(addrSite&);
    bool empty();
};