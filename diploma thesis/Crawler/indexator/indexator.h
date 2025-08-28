#pragma once
#include <string>
#include <vector>
#include <exception>
#include "../data base/DBclass.h"
#include <memory>
#include "addrSite.h"

class indexator {
    std::shared_ptr<DBclass> DB;
    int addedS = 0, addedW = 0, updatedW = 0;
     
    const int minSizeWord = 3; // >= 1
    const int maxSizeWord = 20;
    const std::string delitedChar { ",./\\|\"\'\t\n\r\f\a\b\v!@#$%^?�&*(){}[]-_=+;:~`" };
    const std::vector<std::string> rangeTags { "style", "script", "code", "button"};

    std::vector<std::string> blackListSite;
    std::vector<addrSite> links;
    
    void cleanerText(std::string&, std::string& tit, const addrSite& currAddr);
    void readBlackList();
    void inputBD(const addrSite&,const std::string& tit, const std::vector<std::string>& wrd);
public:
    indexator(std::shared_ptr<DBclass> );
    void indexation(std::string& body, const addrSite& site);
    std::vector<addrSite>&& getLinks();
    void getAdded(int& site, int& word, int& updWord);
};

class errorOfTextSite :public std::exception {};
