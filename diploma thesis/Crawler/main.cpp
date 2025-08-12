#include <iostream>
#include "DBclass.h"
#include <memory>
#include "ini-parser/parser.h"
#include "iterateSite.h"

//#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "internet/httpServer.h"
//#include "data base/DBsimulation.h"
#include "data base/DBclass.h"


std::string fuunka(std::string str) {
    return str + "---";
}



int main() {
    setlocale(LC_ALL, "Russian");
    setlocale(LC_NUMERIC, "C");    
    //std::locale::global(std::locale(""));
    try {
        ini_parser parser("crawler_data.ini");
        std::shared_ptr<DBclass> DB = std::make_shared<DBclass>(parser);
        

        int threadMax = std::thread::hardware_concurrency();
        if (threadMax >= 4)
            threadMax = threadMax - 2;

        iterateSite iterSite(parser, DB, threadMax);
        iterSite.scanning();
        std::cout << "Server is ran" << std::endl;
        //HTTPserver server(parser, &DB);
        HTTPserver serv(parser, DB);
        
        using namespace std::literals::chrono_literals;
        std::this_thread::sleep_for(2s);

        char stoooop;
        std::cin >> stoooop;
    }
    catch (std::exception& except) {
        std::cout << except.what();
    }
    return 0;
}