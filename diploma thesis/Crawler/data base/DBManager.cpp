#include "DBManager.h"
#include "../my_utilites.h"


DBclass::DBclass(std::unique_ptr<ini_parser> ini) {
    std::string host = ini->get_value<std::string>("DB.host");
    std::string port = ini->get_value<std::string>("DB.port");
    std::string DBname = ini->get_value<std::string>("DB.name");
    std::string user = ini->get_value<std::string>("DB.user");
    std::string password = ini->get_value<std::string>("DB.password");

    std::string str{ "host=" + host + 
        " port=" + port + 
        " dbname=" + DBname + 
        " user=" + user +
        " password=" + password };
    pqxx::connection c(str);
        
    connect = std::move(c);
}

void DBclass::todo(std::wstring str) {
    pqxx::work tr{ connect };
    tr.exec(convertWStrToStr(str));    
    tr.commit();
}

//template<typename Ret>
std::vector<responseSelect> DBclass::selectMult(std::wstring req/*, std::string url, std::string c*/) {
    pqxx::work tr{ connect };    
    std::string url, c;
    std::vector<responseSelect> result;

    for (auto [url, c] :
        tr.query<std::string, int>(convertWStrToStr(req))
        )
    {
        responseSelect tmpl{ url,c };
        result.push_back(tmpl);
    }
    return result;
}

std::string DBclass::select(std::wstring req/*, std::string url, std::string c*/) {
    pqxx::work tr{ connect };
    return tr.query_value<std::string>(convertWStrToStr(req));
}