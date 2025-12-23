#pragma once
#include <pqxx/pqxx>
#include <memory>
#include <utility>
#include "../ini-parser/parser.h"



class DBclass {
    std::unique_ptr<pqxx::connection> connect;
    const int lnghtWord = 20, lnghtUrl = 100, lnghtTitle = 30;

    void createTables();
public:
    DBclass(ini_parser&);
    ~DBclass() = default;
    pqxx::connection& getConn();    
    std::pair<int, int> status();
    const int lengthWord() { return lnghtWord; }
    const int lengthUrl() { return lnghtUrl; }
    const int lengthTitle() { return lnghtTitle; }
 };




