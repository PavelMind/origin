#include "iterateSite_old.h"
#include "httpClient.h"
#include <iostream>
#include <utility>
#include <functional>



bool processedSitesSet::have(addrSite site) {
    std::lock_guard<std::mutex> m{ mut };
    bool have;
    have = s.find(site) != s.end();
    if (have) {
        return true;
    }
    else {
        s.insert(site);
        return false;
    }
}


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




void iterateSite::scanningg() {
    std::cout << "Start of scaning" << std::endl;
    try{
        auto f = pool.submit(std::bind(&iterateSite::work, this, start, countRecurs));
        std::string tmp = f.get();
    }
    catch (std::exception& e) {
        std::cout << "\nError of download to website page:\n" << e.what() << std::endl;
    }

    std::cout << "\nEnd of scaning" << std::endl;
    int addS, addW, updW;
    indexat.getAdded(addS, addW, updW);
    std::cout << "Be added: " << addS << " sites, " << addW << " words; be update: " << updW << std::endl;
}

std::string iterateSite::work(addrSite site, int count) {
    if (procSites2.have(site))
        return "is prcsed";
    
    auto text = downloadSite(site);

    std::string ouuRecCnt{ "Recurs lvl: " + std::to_string(count) + ". Site: " + site.url() + "\n" };
    std::cout << ouuRecCnt;
    
    std::vector<addrSite> links;
    
    try {
        indexat.indexation(text, site, links);
    }
    catch (errorOfTextSite& errText) {
        std::cout << "\nError. Not correct code of website page.\n";
        return false;
    }
    catch (std::exception& e) {
        std::cout << "\nError of indexation:\n" << e.what() << std::endl;
        return false;
    }

    if (count > 0) {
        std::vector<std::future<std::string>> vec;
        for (auto i : links) {
            auto f = pool.submit(std::bind(&iterateSite::work, this, i, count - 1));
            vec.push_back(std::move(f));
        }
        for (auto& i : vec) {
            try {
                std::string tmp = i.get();
                std::string procsed{ " --Was processed " + tmp + "\n" };
                std::cout << procsed;
            }
            catch (std::exception& e) {
                std::cout << "\nError of download to website page:\n" << e.what() << std::endl;
                continue;
            }
        }
    }
    return site.url();
}
