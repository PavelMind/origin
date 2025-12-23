#include <iostream>
#include <memory>
#include "DBclass.h"
#include "ini-parser/parser.h"
#include "internet/httpServer.h"

int main() {
    setlocale(LC_ALL, "Russian");
    setlocale(LC_NUMERIC, "C");
    using namespace std::literals::chrono_literals;
    try {
        ini_parser parser("crawler_data.ini");
        std::shared_ptr<DBclass> DB = std::make_shared<DBclass>(parser);
        std::this_thread::sleep_for(1s);

        auto status = DB->status();
        std::cout << "Data base have URL: " << status.first << "; words: " << status.second << std::endl;
        
        HTTPserver serv(parser, DB);
        std::cout << "Server is ran" << std::endl;
        std::cout << "Input char for stoped" << std::endl;
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