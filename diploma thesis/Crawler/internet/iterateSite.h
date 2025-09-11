#pragma once
#include <string>
#include <memory>
#include "threads_pool_arg.h"
#include "parser.h"
#include "indexator.h"
#include "DBclass.h"
#include "addrSite.h"
#include "listLinks.h"


class iterateSite {
    thread_pool_a pool;
    std::shared_ptr<listLinks> links;
    indexator indexat;
    std::shared_ptr<DBclass> DB;

    int countRecurs;
    addrSite start;
    
    std::string downloadSite(addrSite site);
    bool work(addrSite site, int count);
public:
    iterateSite(ini_parser& p, std::shared_ptr<DBclass> db, int thrdCount);
    void scanning();
};