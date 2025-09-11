#include "httpClient.h"
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <iostream>
#include <exception>

HTTPclient::HTTPclient(std::string hhost): clnt(hhost), host(hhost) {
#ifdef CPPHTTPLIB_OPENSSL_SUPPORT
    clnt.set_ca_cert_path(ca_cert);
    clnt.enable_server_certificate_verification(true);    
#endif
    clnt.set_connection_timeout(6, 0);//6 secund
}

HTTPclient::HTTPclient(std::string hhost, int port) : clnt(hhost, port),host(hhost) {
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
        std::string strErr{ "HTTP client error: " + httplib::to_string(err) + ":" };
        throw
            std::exception(std::string{ strErr + host + target + "\n" }.c_str());
        //return std::string{};
    }
}
#undef CPPHTTPLIB_OPENSSL_SUPPORT