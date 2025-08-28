#include <iostream>
#include "DBclass.h"
#include <memory>
#include "ini-parser/parser.h"
#include "iterateSite.h"
#include "internet/httpServer.h"


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
        auto status = DB->status();
        std::cout << "Data base have URL: " << status.first << "; words: " << status.second << std::endl;

        HTTPserver serv(parser, DB);
        std::cout << "Server is ran" << std::endl;
        std::cout << "Input char for stoped" << std::endl;
        using namespace std::literals::chrono_literals;
        std::this_thread::sleep_for(1s);
        
        
        char stoooop;
        std::cin >> stoooop;
    }
    catch (pqxx::sql_error& erPQXX) { 
        std::cout << erPQXX.what(); 
    }
    catch (std::exception& except) {
        std::cout << except.what();
    }
    return 0;
}