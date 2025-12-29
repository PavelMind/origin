#pragma once
#include <httplib.h>
#include <string>
#include <thread>
#include <memory>
#include <vector>
#include "../ini-parser/parser.h"
#include "../data base/DBclass.h"


class HTTPserver {
    const char* cert = "./cert.pem";
    const char* key = "./key.pem";
#ifdef CPPHTTPLIB_OPENSSL_SUPPORT
    httplib::SSLServer serv;
#else
    httplib::Server serv;
#endif   
    std::string mainHTML;
    std::thread thrd;
    std::shared_ptr<DBclass> DB;
    bool errServer = false;
    
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

