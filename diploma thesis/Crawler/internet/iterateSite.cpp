#include "iterateSite.h"
#include <iostream>
#include "httpClient.h"
#include <utility>


std::string downloadSite(addrSite site) {
    HTTPclient client(site.host());
    return client.Get(site.path());
}



iterateSite::iterateSite(ini_parser& p, std::shared_ptr<DBclass> db, int thrdCount) :
    pool(thrdCount), DB(db), indexat(db) {
        try {
            countRecurs = p.get_value<int>("spider.recurs");
            std::string str = p.get_value<std::string>("spider.start");
            start = addrSite(str);
            if (!start.ref())
                throw std::exception("Not correct site into INI-file. Set default.");
        }
        catch (myexpect& mye) {
            std::wcout << mye.what();
            std::cout << "In line:" << mye.numberErrLine();
            start = addrSite("https://example.com/");
            countRecurs = 1;
        }
        catch (std::exception& e) {
            std::cout << e.what();
            start = addrSite("https://example.com/");
            countRecurs = 1;
        }

}

bool iterateSite::isProcessed(addrSite& site) {
    if (processedSites.find(site) == processedSites.end())
    {
        return false;
    }
    else
        return true;
}

void iterateSite::scanning() {
    std::cout << "Start of scaning" << std::endl;
    int count = countRecurs;
    std::string textSite;
    bool needProces = !isProcessed(start);
    try {
        if (needProces) {
            //auto resFuture = pool.submit(&downloadSite, this, start);
            auto resFuture = pool.submit(downloadSite, start);
            textSite = resFuture.get();
        }
    }
    catch (std::exception& e) {
        std::cout << "Error of download to website page:\n" << e.what() << std::endl;
        return;
    }

    if(needProces)
        recursScan(textSite, start, count - 1);
    std::cout << "\nEnd of scaning" << std::endl;
    int addS, addW, updW;
    indexat.getAdded(addS, addW, updW);
    std::cout << "Be added: " << addS << " sites, " << addW << " words; be update: " << updW << std::endl;
}

void iterateSite::recursScan(std::string& text, const addrSite& site, int count) {
    std::cout << "Recurs lvl: "<<count << ". Site: " << site.url() << std::endl;
    try { 
        processedSites.insert(site);
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
        std::vector< std::pair<std::string, int> > textSites;
        std::vector< std::pair<std::future<std::string>, int> > futureSites;

        for (auto i = 0; i < siteList.size(); ++i) {
            try {
                if (!isProcessed(siteList[i])) {
                    //auto f = pool.submit(&downloadSite, this, s);
                    auto f = pool.submit(downloadSite, siteList[i]);
                    futureSites.push_back({ std::move(f), i });
                }
            }
            catch (std::exception& e) {
                std::cout << "Error in pool.submit(): " << e.what() << std::endl;
            }
        }

        for (auto i = 0; i < futureSites.size(); ++i) {
            try {
                auto text = futureSites[i].first.get();
                std::pair<std::string, int> pr(std::move(text), futureSites[i].second);
                textSites.push_back(std::move(pr));
            }
            catch (std::exception& e) {
                std::cout << "\nError of download to website page:\n" << e.what() << std::endl;
                continue;
            }
        }
        for (auto i = 0; i < textSites.size(); ++i) {
            auto sit = siteList[textSites[i].second];
            recursScan(textSites[i].first, sit, count-1);
        }
    }
    else
        return;
}