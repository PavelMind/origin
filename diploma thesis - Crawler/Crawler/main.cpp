#include <iostream>
#include <memory>
#include "DBclass.h"
#include "ini-parser/parser.h"
#include "iterateSite.h"

int main() {
    setlocale(LC_ALL, "Russian");
    setlocale(LC_NUMERIC, "C");
    using namespace std::literals::chrono_literals;
    try {
        ini_parser parser("crawler_data.ini");
        std::shared_ptr<DBclass> DB = std::make_shared<DBclass>(parser);

        int threadMax = std::thread::hardware_concurrency();
        if (threadMax >= 4)
            threadMax = threadMax - 2;
        iterateSite iterSite(parser, DB, threadMax);
        std::this_thread::sleep_for(1s);
        iterSite.scanning();
        auto status = DB->status();
        std::cout << "Data base have URL: " << status.first << "; words: " << status.second << std::endl;

    }
    catch (pqxx::sql_error& erPQXX) { 
        std::cout << erPQXX.what(); 
    }
    catch (std::exception& except) {
        std::cout << except.what();
    }
    return 0;
}