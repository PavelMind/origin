#pragma once
#include <string>
#include <vector>
#include <exception>
#include "../data base/DBclass.h"
#include <memory>
#include <mutex>
#include "addrSite.h"

class indexator {
    std::shared_ptr<DBclass> DB;
    int addedS = 0, addedW = 0, updatedW = 0;
    std::mutex mtxDB, mtxBlack;
     
    const int minSizeWord = 3; // >= 1
    const int maxSizeWord = 20;
    const static std::string delitedChar;
    const static std::vector<std::string> rangeTags;

    std::vector<std::string> blackListSite;
    //std::vector<addrSite> links;
    
    void cleanerText(std::string&, std::string& tit, const addrSite& currAddr, std::vector<addrSite>& link);
    void readBlackList();
    void inputBD(const addrSite&,const std::string& tit, const std::vector<std::string>& wrd);
public:
    indexator(std::shared_ptr<DBclass> );
    void indexation(std::string& body, const addrSite& site, std::vector<addrSite>& link);
    std::vector<addrSite>&& getLinks();
    void getAdded(int& site, int& word, int& updWord);

};



class errorOfTextSite :public std::exception {};
