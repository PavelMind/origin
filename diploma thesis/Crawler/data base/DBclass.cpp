#include "DBclass.h"
//#include "../my_utilites.h"
#include <iostream>


DBclass::DBclass(ini_parser& ini) {
    std::string host;
    std::string port;
    std::string DBname;
    std::string user;
    std::string password;
    try{
        host = ini.get_value<std::string>("DB.host");
        port = ini.get_value<std::string>("DB.port");
        DBname = ini.get_value<std::string>("DB.name");
        user = ini.get_value<std::string>("DB.user");
        password = ini.get_value<std::string>("DB.password");
    }
    catch (myexpect& mye) {
        std::wcout << mye.what();
        std::cout << "In line:" << mye.numberErrLine();        
    }
    catch (std::exception& e) {
        std::cout << e.what();
    }
    //try {
        std::string str{ "host=" + host +
            " port=" + port +
            " dbname=" + DBname +
            " user=" + user +
            " password=" + password };
        pqxx::connection c(str);

        connect = std::move(c);
    /*}
    catch (pqxx::sql_error& erPQXX) { std::cout << erPQXX.what(); }
    catch (std::exception& e) { std::cout << e.what(); }*/

    createTables();
}

pqxx::connection& DBclass::getConn() {
    return connect;
}

void DBclass::createTables() {    
    try {
        pqxx::work tr{ connect };
        tr.exec("CREATE TABLE IF NOT EXISTS sites(\
            id SERIAL PRIMARY KEY,\
            title VARCHAR(30),\
            URL VARCHAR(50) UNIQUE NOT NULL);");

        tr.exec("CREATE TABLE IF NOT EXISTS words (\
            id SERIAL PRIMARY KEY,\
            word VARCHAR(20) NOT NULL);");

        tr.exec("CREATE TABLE IF NOT EXISTS counts (\
            id_site INTEGER NOT NULL REFERENCES sites(id),\
            id_word INTEGER NOT NULL REFERENCES words(id),\
            count_word INTEGER NOT NULL);");
        tr.commit();
    }
    catch (pqxx::sql_error& erPQXX) { std::cout << erPQXX.what(); }
    catch (std::exception& e) { std::cout << e.what(); }
}


void DBclass::todo(std::string str) {
    pqxx::work tr{ connect };
    tr.exec(str);
    tr.commit();
}


std::vector<respSelSiteList> DBclass::selectSiteList(std::string req) {
    pqxx::work tr{ connect };    
    std::string url;
    std::string nm;
    int c;
    std::vector<respSelSiteList> result;
    
    for (auto [nm, url, c] : tr.query<std::string, std::string, int>(req) )
    {
        respSelSiteList tmpl{ nm, url, c };
        result.push_back(tmpl);
    }
    return result;
}

std::vector<int> DBclass::selectMultInt(std::string req) {
    pqxx::work tr{ connect };
    int c;
    std::vector<int> result;

    for (auto [c] : tr.query<int>(req)  )
    {        
        result.push_back(c);
    }
    return result;
}


