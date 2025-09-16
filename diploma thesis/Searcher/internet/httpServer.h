#pragma once
#include <httplib_S.h>
#include <string>
#include <thread>
#include <memory>
#include <vector>
#include "../ini-parser/parser.h"
#include "../data base/DBclass.h"


class HTTPserver {
    const char* cert = "./cert.pem";
    const char* key = "./key.pem";
#ifdef S_CPPHTTPLIB_OPENSSL_SUPPORT_S
    httplib_S::SSLServer serv;
#else
    httplib_S::Server serv;
#endif   
    std::string mainHTML;
    std::thread thrd;
    std::shared_ptr<DBclass> DB;
    
    void readMyStartHtml();
    std::string createListResp(std::string);
    void createListWords(std::vector<std::string>&, const std::string&);
    std::vector<std::pair<std::string, std::string>> reqFromDB(const std::vector<std::string>&);
public:
    HTTPserver(std::string, int, std::shared_ptr<DBclass> );
    HTTPserver(ini_parser&, std::shared_ptr<DBclass> );
    ~HTTPserver();

    HTTPserver(const HTTPserver&) = delete;
    HTTPserver& operator=(const HTTPserver&) = delete;
    
    void stop();
};

