#pragma once
#include <pqxx/pqxx>
#include <string>
#include "../ini-parser/parser.h"

struct respSelSiteList {
    std::string name;
    std::string URL;
    int count;
};

class DBclass {
    pqxx::connection connect;

    void createTables();
public:
    DBclass(ini_parser&);
    ~DBclass() = default;
    pqxx::connection& getConn();

    
    void todo(std::string query);
    
    std::vector<respSelSiteList> selectSiteList(std::string);
    std::vector<int> selectMultInt(std::string);
    
    
    //template<typename TableType, typename ...ArgT>
    //std::vector<TableType> selectMult(std::string, ArgT...);
 };

//template<typename TableType, typename ...ArgT>
//std::vector<TableType> DBclass::selectMult(std::string req, ArgT... fields) {
//    pqxx::work tr{ connect };
//
//    std::vector<TableType> result;
//
//    for (auto [fields] :
//        tr.query<ArgT...>(req)
//        )
//    {
//        TableType tmpl{ fields };
//        result.push_back(tmpl);
//    }
//    return result;
//}



