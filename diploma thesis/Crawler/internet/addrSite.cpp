#include "addrSite.h"
#include <iostream>
#include <algorithm>

const std::vector<std::string> addrSite::siteFile={ ".html", ".shtml", ".htm", ".php" };

addrSite::addrSite(bool b, std::string h, std::string p): _host(h), _path(p) {
    if (b)
        protocol = https;
    else
        protocol = http;
}

addrSite::addrSite() { protocol = other; }

addrSite::addrSite(std::string url, const addrSite curr) {    
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
        protocol = curr.protocol;
        _host = curr._host;
        if (url.substr(0, 3) == "../")
            relativeLinkBack(url, curr);
        else if (url[0] == '/')
            relativeLinkSlash(url, curr);
        else
            relativeLink(url, curr);
    }
    int anchor = _path.find('#');
    if (anchor != -1) {
        _path.resize(anchor);
    }
}

void addrSite::relativeLink(std::string& newPh, const addrSite& curr) {
    std::string CuPath = curr._path;
    bool isFile = false;
    int lastSl = CuPath.find_last_of('/', CuPath.size()-2);

    for (auto& i : siteFile) {
        int p = CuPath.rfind(i);
        if (p != -1 && p > lastSl) {
            isFile = true;
            break;
        }
    }
    if (isFile) {
        CuPath.erase(lastSl);
    }
    if (CuPath.back() != '/')
        CuPath.push_back('/');

    _path = CuPath + newPh;
}

void addrSite::relativeLinkSlash(std::string& newPh, const addrSite& curr) {
    _path = newPh;
}

void addrSite::relativeLinkBack(std::string& newPh, const addrSite& curr) {    
    std::string CPath = curr._path;

    while (newPh.substr(0, 3) == "../") {
        newPh.erase(0, 3);
        int pDelSl = 0;
        if (CPath != "/") {
            if (CPath[CPath.size() - 1] == '/') {   //  "/....../"
                pDelSl = CPath.find_last_of('/', CPath.size() - 2);
            }
            else {  //  "/....."
                pDelSl = CPath.find_last_of('/');
            }
            CPath.erase(pDelSl + 1);
        }
        else {
            std::cout << "Not correct link url: child:\"../\", perent path:\"/\".\n";
            std::cout << "parent url: " << curr.url() << ", child path: " << newPh << std::endl;
        }
    }
    _path = CPath + newPh;
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
    int anchor = _path.find('#');
    if (anchor != -1) {
        _path.resize(anchor);
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
    bool notFile = true;

    int p = _path.find_last_of(".");
    if (p != -1) {
        std::string strFile = _path.substr(p);
        if (std::find(siteFile.begin(), siteFile.end(), strFile) == siteFile.end())
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
        return "Not site protocol:"; // -> not to connect
    res += _host + _path;
    if (res.back() == '/')
        res.pop_back();
    return res;
}

bool operator <(const addrSite& a1, const addrSite& a2) {
    if (a1.url() < a2.url()) 
        return true;
    else
        return false;
}