#include "iterateSite.h"
#include <iostream>
#include "httpClient.h"
#define CPPHTTPLIB_OPENSSL_SUPPORT
//#include "../my_utilites.h"


std::string downloadSite(std::string site) {
    std::string host, target;
    auto begHost = 0;
    auto p = site.find("http://");
    if (p != -1)
        begHost = 7;
    else {
        p = site.find("https://");
        if (p != -1)
            begHost = 8;
        else
            begHost = 0;
    }
    auto endHost = site.find("/", begHost);
    if (endHost == -1) {
        host = site.substr(begHost);
        target = "/";
    }
    else {
        host = site.substr(begHost, endHost - begHost);
        target = site.substr(endHost);
    }

    HTTPclient client(host);

    return client.Get(target);
}

iterateSite::iterateSite(ini_parser& p, std::shared_ptr<DBclass> db, int thrdCount) :
    pool(thrdCount), indexat(db) {
        try {
            countRecurs = p.get_value<int>("spider.recurs");
            start = p.get_value<std::string>("spider.start");
        }
        catch (myexpect& mye) {
            std::wcout << mye.what();
            std::cout << "In line:" << mye.numberErrLine();
            start = "https://example.com/";
            countRecurs = 1;
        }
        catch (std::exception& e) {
            std::cout << e.what();
            start = "https://example.com/";
            countRecurs = 1;
        }

}

void iterateSite::scanning() {
    std::cout << "Start of scaning" << std::endl;
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

    recursScan(textSite, start, --count);
    std::cout << "\nEnd of scanong" << std::endl;
}

void iterateSite::recursScan(std::string& text, const std::string& site, int count) {
    //multString textSite = convertStr_to_W(text);
    std::cout << "Scaning to Recursiv level: " << count << std::endl;
    try {
        std::cout << "Site Ok: " << processedSite++ << "\r";
        indexat.indexation(text, site);
    }
    catch (errorOfTextSite& errText) {
        std::cout << "\nError. Not correct code of website page.\n";
        return;
    }
    catch (std::exception& e) {
        std::cout << "\nError of indexation:\n" << e.what() << std::endl;
        return;
    }

    if (count > 0) {
        auto siteList = indexat.getLinks();
        std::vector<std::string> textUndeSites;
        std::vector<std::future<std::string>> futureSites;

        for (auto& i : siteList) {
            auto f = pool.submit(downloadSite, i);
            futureSites.push_back(std::move(f));
        }
        for (auto& fut : futureSites) {
            try {
                auto text = fut.get();
                textUndeSites.push_back(std::move(text));
            }
            catch (std::exception& e) {
                std::cout << "\nError of download to website page:\n" << e.what() << std::endl;
                continue;
            }
        }
        for (auto i = 0; i < textUndeSites.size(); ++i) {
            recursScan(textUndeSites[i], siteList[i], --count);
        }
    }
    else
        return;
}