#pragma once
#include <string>
#include "threads pool/threads_pool_arg.h"
#include "ini-parser/parser.h"
#include "indexator/indexator.h"
#include <iostream>


std::string downloadSite(std::string site);



class iterateSite {
    thread_pool_a pool;
    indexator indexat;
    int countRecurs;
    std::string start;

    void recursScan(const std::string& site, int count);
public:
    iterateSite(ini_parser& p, int thrdCount);
    void scanning();
};