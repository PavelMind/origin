#pragma once
#include <string>
#include "threads_pool_arg.h"
#include "parser.h"
#include "indexator.h"
#include "../data base/DBclass.h"
#include <memory>

//#include "../data base/DBsimulation.h"



std::string downloadSite(std::string site);

class iterateSite {
    thread_pool_a pool;
    indexator indexat;
    int countRecurs;
    std::string start;
    int processedSite = 0;

    
    void recursScan(std::string&, const std::string&, int count);
public:
    iterateSite(ini_parser& p, std::shared_ptr<DBclass> db, int thrdCount);
    void scanning();
};