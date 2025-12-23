#pragma once
#include <string>
#include <vector>
#include <exception>
#include <memory>
#include <mutex>
#include "DBclass.h"
#include "addrSite.h"
#include "listLinks.h"


class indexator {
    std::shared_ptr<DBclass> DB;
    std::shared_ptr<listLinks> prLinks;
    int addedS = 0, addedW = 0, updatedW = 0;
    std::mutex mtxDB, mtxBlack;
     
    const int minSizeWord = 3; // >= 1
    const int maxSizeWord = 20;
    const static std::string delitedChar;
    const static std::vector<std::string> rangeTags;
    std::vector<std::string> blackListSite;

    void cleanerText(std::string&, std::string& tit, const addrSite& currAddr);
    void readBlackList();
    void inputBD(const addrSite&,const std::string& tit, const std::vector<std::string>& wrd);
public:
    indexator(std::shared_ptr<DBclass>, std::shared_ptr<listLinks>);
    void indexation(std::string& body, const addrSite& site);
    void getAdded(int& site, int& word, int& updWord);
};

class errorOfTextSite :public std::exception {};
