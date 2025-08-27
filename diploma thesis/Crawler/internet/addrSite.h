#pragma once
#include <string>

class addrSite {
    enum protocolType {
        http,
        https,
        other
    };
    protocolType protocol;
    std::string _host;
    std::string _path;
public:
    addrSite(bool isSSL, std::string host, std::string path);
    explicit addrSite(std::string);
    addrSite(std::string _new, bool currSll, std::string currHost);
    addrSite();
    addrSite& operator =(const addrSite&);
    bool operator ==(const addrSite&);
    friend bool operator <(const addrSite&, const addrSite&);

    bool SSL() const;
    bool ref() const;
    std::string host() const;
    std::string path() const;
    std::string url() const;
};

bool operator <(const addrSite&, const addrSite&);