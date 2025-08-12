#pragma once
#include <string>
#include <vector>
#include <exception>
#include "../data base/DBclass.h"
//#include "../data base/DBsimulation.h"
#include <memory>
//#include "../my_utilites.h"

class indexator {
    std::shared_ptr<DBclass> DB; 
    
     
    const int minSizeWord = 3; // >= 1
    const int maxSizeWord = 20;
    const std::string delitedChar { ",./\\|\"\'\t\n\r\f\a\b\v!@#$%^?¹&*(){}[]-_=+;:~`" };
    const std::vector<std::string> rangeTags { "style", "script", "code", "button", "div"};

    std::vector<std::string> links;
    
    void cleanerText(std::string&, std::string&);
    void inputBD(const std::string&,const std::string&, const std::string&);
public:
    indexator(std::shared_ptr<DBclass> );
    void indexation(std::string& body, const std::string& site);
    std::vector<std::string>&& getLinks();
    //void cleanLinks();
};

class errorOfTextSite :public std::exception {};
