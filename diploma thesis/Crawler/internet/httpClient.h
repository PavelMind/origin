#pragma once
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <httplib.h>
#include <string>


class HTTPclient {
    const char* ca_cert = "./ca-bundle.crt";
#ifdef CPPHTTPLIB_OPENSSL_SUPPORT
    httplib::SSLClient clnt;
#else
    httplib::Client clnt;
#endif

public:
    HTTPclient(std::string host);
    HTTPclient(std::string host, int port);
    HTTPclient();// "localhost"
    std::string Get(std::string site); //return body of site
};

#undef CPPHTTPLIB_OPENSSL_SUPPORT