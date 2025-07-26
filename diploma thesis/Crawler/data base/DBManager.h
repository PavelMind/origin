#pragma once
#include <pqxx/pqxx>
#include <string>
#include <exception>
#include "../ini-parser/parser.h"
#include <memory>


struct responseSelect {
    std::string URL;
    int count;
};

class DBclass {
    pqxx::connection connect;
public:
    DBclass(std::unique_ptr<ini_parser>);
    ~DBclass() = default;
    void todo(std::wstring query);

    
    std::vector<responseSelect> selectMult(std::wstring);
    std::string select(std::wstring);
 };

