#pragma once
#include <string>
#include "threads_pool_arg.h"
#include "parser.h"
#include "indexator.h"
#include "../data base/DBclass.h"
#include <memory>
#include "addrSite.h"
#include <set>
#include <mutex>

class processedSitesSet {
    std::set<addrSite> s;
    std::mutex mut;
public:
    bool have(addrSite);
};



std::string downloadSite(addrSite site);

class iterateSite {
    thread_pool_a pool;
    indexator indexat;
    std::shared_ptr<DBclass> DB;
    int countRecurs;
    addrSite start;
    processedSitesSet procSites2;

    std::string work(addrSite site, int count);
    //bool isProcessed(const addrSite&); //true if have into DB
    //void recursScan(std::string&, const addrSite&, int count);
public:
    iterateSite(ini_parser& p, std::shared_ptr<DBclass> db, int thrdCount);
    void scanningg();

    
};