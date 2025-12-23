#pragma once
#include <string>
#include <vector>

class addrSite {
    const static std::vector<std::string> typeFile;
    enum protocolType {
        http,
        https,
        other
    };
    protocolType protocol;
    std::string _host;
    std::string _path;

    void relativeLink(std::string& _new, const addrSite& curr);
    void relativeLinkSlash(std::string& _new, const addrSite& curr);
    void relativeLinkBack(std::string& _new, const addrSite& curr);
public:
    addrSite(bool isSSL, std::string host, std::string path);
    explicit addrSite(std::string);
    addrSite(std::string _new, const addrSite curr);
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