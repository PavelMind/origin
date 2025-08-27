#include "httpClient.h"
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <iostream>

HTTPclient::HTTPclient(std::string host): clnt(host) {
#ifdef CPPHTTPLIB_OPENSSL_SUPPORT
    clnt.set_ca_cert_path(ca_cert);
    clnt.enable_server_certificate_verification(true);    
#endif
    clnt.set_connection_timeout(6, 0);//6 secund
}

HTTPclient::HTTPclient(std::string host, int port) : clnt(host, port) {
#ifdef CPPHTTPLIB_OPENSSL_SUPPORT
    clnt.set_ca_cert_path(ca_cert);
    clnt.enable_server_certificate_verification(true);    
#endif
    clnt.set_connection_timeout(6, 0);//6 secund
}

HTTPclient::HTTPclient() : HTTPclient("localhost") {}

std::string HTTPclient::Get(std::string target) {
    

    auto res = clnt.Get(target);
    if (res && res->status == 301) {
        clnt.set_follow_location(true);
        res = clnt.Get(target);
    }

    if (res && res->status == httplib::StatusCode::OK_200) {
        return res->body;
    }
    else {
        auto err = res.error();
        std::cout << "HTTP error: " << httplib::to_string(err) << std::endl;
        return " ";
    }
}
#undef CPPHTTPLIB_OPENSSL_SUPPORT