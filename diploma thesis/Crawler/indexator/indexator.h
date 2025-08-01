#pragma once
#include <string>
#include <vector>
#include <exception>
#include "../my_utilites.h"

class indexator {
    const int minSizeWord = 3; // >= 1
    const int maxSizeWord = 20;
    const multString delitedChar { L",./\\|\"\'\t\n\r!@#$%^?¹&*(){}[]-_=+;:~`" };
    const std::vector<multString> rangeTags { L"style", L"script", L"code"};

    std::vector<std::string> links;
    
    void cleanerText(multString&);
    void inputBD(const multString&);
public:
    void indexation(multString&);
    std::vector<std::string>&& getLinks();
    //void cleanLinks();
};

class errorOfTextSite :public std::exception {};
