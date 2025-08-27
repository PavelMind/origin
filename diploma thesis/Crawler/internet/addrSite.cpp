#include "addrSite.h"
#include <iostream>

addrSite::addrSite(bool b, std::string h, std::string p): _host(h), _path(p) {
    if (b)
        protocol = https;
    else
        protocol = http;
}

addrSite::addrSite() { protocol = other; }

addrSite::addrSite(std::string url, bool currS, std::string currH) {
    int size = url.size();
    int p = 0;
    p = url.find("://");
    if (p != -1) {
        std::string prot = url.substr(0, p);
        if (prot == "http") {
            protocol = http;            
        }
        else if(prot == "https"){
            protocol = https;
        }
        else  {
            protocol = other;
        }
        p += 3;
        int g = url.find("/", p);
        if (g != -1) {
            _host = url.substr(p, g - p);
            _path = url.substr(g);
        }
        else {
            _host = url.substr(p);
            _path = "/";
        }

    }
    else {
        if (currS) {
            protocol = https;
        }
        else {
            protocol = http;
        }
        _host = currH;
        if (url[0] == '/')
            _path = url;
        else
            _path = "/" + url;
    }
}

addrSite::addrSite(std::string url) {
    int p = 0;
    p = url.find("://");
    if (p == -1) {
        std::cout << "\nNot correct url into constructor: " << url << "|\n";
        protocol = other;
        return;
    }
    std::string str = url.substr(0, p);
    if (str == "http") {
        protocol = http;
    }
    else if (str == "https") {
        protocol = https;
    }
    else {
        protocol = other;
    }
    p += 3;
    int b = url.find("/", p);
    if (b != -1) {
        _host = url.substr(p, b - p);
        _path = url.substr(b);
    }
    else {
        _host = url.substr(p);
        _path = "/";
    }
}

addrSite& addrSite::operator =(const addrSite& oth) {
    protocol = oth.protocol;
    _host = oth._host;
    _path = oth._path;
    return *this;
}

bool addrSite::operator ==(const addrSite& oth) {
    return protocol == oth.protocol && _host == oth._host && _path == oth._path;
}


bool addrSite::SSL() const {
    return protocol == https;
}

bool addrSite::ref() const {
    bool prot = (protocol == https || protocol == http);
    int p = _path.find_last_of(".");
    bool notFile;
    if (p == -1) {
        notFile = true;
    }
    else {
        if ( (_path.substr(p) == ".html") || (_path.substr(p) == ".shtml"))
            notFile = true;
        else
            notFile = false;
    }
    return prot && notFile;
}

std::string addrSite::host() const {
    return _host;
}

std::string addrSite::path() const {
    return _path;
}

std::string addrSite::url() const {
    std::string res;
    if (protocol == https) {
        res = "https://";
    }
    else if (protocol == http)
        res = "http://";
    else
        return "bad protocol"; // -> not to connect
    res += _host + _path;
    return res;
}

bool operator <(const addrSite& a1, const addrSite& a2) {
    if (a1.url() < a2.url()) 
        return true;
    else
        return false;
}