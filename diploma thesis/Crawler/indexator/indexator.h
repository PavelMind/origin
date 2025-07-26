#pragma once
#include <string>
#include <vector>
#include <exception>

class indexator {
    const int minSizeWord = 3; // >= 1
    const int maxSizeWord = 20;
    const std::wstring delitedChar { L",./\\|\"\'\t\n\r!@#$%^?¹&*(){}[]-_=+;:~`" };
    const std::vector<std::wstring> rangeTags { L"style", L"script", L"code"};

    std::vector<std::string> links;
    
    void cleanerText(std::wstring&);
    void inputBD(std::wstring);
public:
    void indexation(std::wstring&);
    std::vector<std::string> getLinks();
    void cleanLinks();
};

class errorOfTextSite :public std::exception {};
