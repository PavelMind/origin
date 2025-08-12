#pragma once
//#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <httplib.h>
#include <string>
#include <thread>
#include "../ini-parser/parser.h"
#include <vector>
#include "../data base/DBclass.h"
#include <memory>

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

    
    void readMyStartHtml();
    std::string createListResp(const std::string);
    void createListWords(std::vector<std::string>&, const std::string&);
    std::vector<std::pair<std::string, std::string>> reqFromDB(const std::vector<std::string>&);
public:
    HTTPserver(std::string, int, std::shared_ptr<DBclass> );
    HTTPserver(ini_parser&, std::shared_ptr<DBclass> );
    ~HTTPserver();
    void stop();
    //void search(std::string&);
};

