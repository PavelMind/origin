#include "DBclass.h"
#include <iostream>
#include "sql_query_builders.h"


DBclass::DBclass(ini_parser& ini) {
    std::string host{"localhost"};
    std::string port{ "5432" };
    std::string DBname{ "crawler" };
    std::string user{"postgres"};
    std::string password{"2806"};
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
    std::string str{ "host=" + host +
            " port=" + port +
            " dbname=" + DBname +
            " user=" + user +
            " password=" + password 
    };

    connect = std::make_unique<pqxx::connection>(str);

    createTables();
}

pqxx::connection& DBclass::getConn() {
    return *connect;
}

void DBclass::createTables() {    
    try {
        pqxx::work tr{ *connect };

        SqlCreateQueryBuilder sites, words, counts;
        sites.AddNameTable("sites").AddKey("id").AddString("title", 30).AddStringUniNN("URL", 50);

        words.AddNameTable("words").AddKey("id").AddStringUniNN("word", 20);

        counts.AddNameTable("counts").AddReference("id_site", "sites", "id").
            AddReference("id_word", "words", "id").AddIntNN("count_word");

        tr.exec(sites.BuildQuery());
        tr.exec(words.BuildQuery());
        tr.exec(counts.BuildQuery());
        tr.commit();
    }
    catch (pqxx::sql_error& erPQXX) { std::cout << erPQXX.what(); }
    catch (std::exception& e) { std::cout << e.what(); }
}

std::pair<int, int> DBclass::status() {
    pqxx::work tr{ *connect };
    auto selectBld = [](const std::string& name) { return "SELECT COUNT(*) FROM " + name + ";"; };
    
    std::string nameTbl{ "sites" };
    std::string req = selectBld(nameTbl);

    int tmp = 0;
    int cntSites = 0;
    int cntWords = 0;

    for (auto [tmp] : tr.query<int>(req))
    {
        cntSites = tmp;
    }

    nameTbl= "words";
    req = selectBld(nameTbl);
    for (auto [tmp] : tr.query<int>(req))
    {
        cntWords = tmp;
    }

    return std::pair{ cntSites , cntWords };
}



void DBclass::todo(std::string str) {
    pqxx::work tr{ *connect };
    tr.exec(str);
    tr.commit();
}


std::vector<respSelSiteList> DBclass::selectSiteList(std::string req) {
    pqxx::work tr{ *connect };    
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
    pqxx::work tr{ *connect };
    int c;
    std::vector<int> result;

    for (auto [c] : tr.query<int>(req)  )
    {        
        result.push_back(c);
    }
    return result;
}


