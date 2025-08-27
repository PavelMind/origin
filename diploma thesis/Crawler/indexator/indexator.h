#pragma once
#include <string>
#include <vector>
#include <exception>
#include "../data base/DBclass.h"
#include <memory>
#include "addrSite.h"

class indexator {
    std::shared_ptr<DBclass> DB; 
     
    const int minSizeWord = 3; // >= 1
    const int maxSizeWord = 20;
    const std::string delitedChar { ",./\\|\"\'\t\n\r\f\a\b\v!@#$%^?¹&*(){}[]-_=+;:~`" };
    const std::vector<std::string> rangeTags { "style", "script", "code", "button", "div"};

    std::vector<std::string> blackListSite;
    std::vector<addrSite> links;
    
    void cleanerText(std::string&, std::string& tit, const addrSite& currAddr);
    void readBlackList();
    void inputBD(const addrSite&,const std::string& tit, const std::vector<std::string>& wrd);
public:
    indexator(std::shared_ptr<DBclass> );
    void indexation(std::string& body, const addrSite& site);
    std::vector<addrSite>&& getLinks();
};

class errorOfTextSite :public std::exception {};
