#include "iterateSite.h"
#include <iostream>
#include "my_utilites.h"


std::string downloadSite(std::string site) {
    std::cout << "NO TO CODE DOWNLOAD SITE IN iterateSite.cpp\n";
    return "site";
}

iterateSite::iterateSite(ini_parser& p, int thrdCount) : pool(thrdCount) {
    countRecurs = p.get_value<int>("spider.recurs");
    start = p.get_value<std::string>("spider.start");
}

void iterateSite::scanning() {
    int count = countRecurs;
    std::string textSite;
    try {
        auto resFuture = pool.submit(downloadSite,start);
        textSite = resFuture.get();
    }
    catch (std::exception& e) {
        std::cout << "Error of download to website page:\n" << e.what() << std::endl;
        return;
    }

    recursScan(textSite, --count);
}

void iterateSite::recursScan(const std::string& text, int count) {
    multString textSite = convertUTF8(text);
    try {
        indexat.indexation(textSite);
    }
    catch (errorOfTextSite& errText) {
        std::cout << "Error. Not correct code of website page.\n";
        return;
    }
    catch (std::exception& e) {
        std::cout << "Error of indexation:\n" << e.what() << std::endl;
        return;
    }

    if (count > 0) {
        auto siteList = indexat.getLinks();
        std::vector<std::string> textUndeSites;
        std::vector<std::future<std::string>> futureSites;

        for (auto& i : siteList) {
            auto f = pool.submit(downloadSite,i);
            futureSites.push_back(std::move(f));
        }
        for (auto& fut : futureSites) {
            try {
                auto text = fut.get();
                textUndeSites.push_back(std::move(text));
            }
            catch (std::exception& e) {
                std::cout << "Error of download to website page:\n" << e.what() << std::endl;
                continue;
            }
        }
        for (auto& text : textUndeSites) {
            recursScan(text, --count);
        }
    }
    else
        return;
}