#include "iterateSite.h"
#include "httpClient.h"
#include <iostream>
#include <utility>
#include <functional>


iterateSite::iterateSite(ini_parser& p, std::shared_ptr<DBclass> db, int thrdCount) :
    pool(thrdCount), DB(db), links{ std::make_shared<listLinks>() }, indexat(db, links) {
        try {
            countRecurs = p.get_value<int>("spider.recurs");
            std::string str = p.get_value<std::string>("spider.start");
            start = addrSite(str);
            if (!start.ref())
                throw std::exception("Not correct site into INI-file. Set default.");
        }
        catch (myexpect& mye) {
            std::wcout << mye.what();
            std::cout << " In line:" << mye.numberErrLine();
            start = addrSite("https://example.com/");
            countRecurs = 1;
        }
        catch (std::exception& e) {
            std::cout << e.what()<<std::endl;
            start = addrSite("https://example.com/");
            countRecurs = 1;
        }
}

std::string iterateSite::downloadSite(addrSite site) {
    HTTPclient client(site.host());
    return client.Get(site.path());
}

void iterateSite::scanning() {
    std::cout << "Start of scaning" << std::endl;
    links->push(start);
    int cntRecurs = countRecurs;
    do {
        std::vector<addrSite> vecSite = std::move(links->getLinks());
        std::vector<std::future<bool>> vecFut;

        for (auto& i : vecSite) {
            try {
                if (!links->isProcAndMarked(i)) {
                    auto f = pool.submit(std::bind(&iterateSite::work, this, i, cntRecurs));
                    vecFut.push_back(std::move(f));
                }
            }
            catch (std::exception& e) {
                std::cout << "Error in pool.submit(): " << e.what() << std::endl;
            }
        }
        
        for (auto& i : vecFut) {
            try {
                auto tmp = i.get();
            }
            catch (std::exception& e) {
                std::cout << "Error of download to website page: " << e.what() << std::endl;
                continue;
            }
        }
        --cntRecurs;
    } while (!links->empty() && cntRecurs > 0);

    std::cout << "\nEnd of scaning" << std::endl;
    int addS, addW, updW;
    indexat.getAdded(addS, addW, updW);
    std::cout << "Be added: " << addS << " sites, " << addW << " words; be update: " << updW << std::endl;
}

bool iterateSite::work(addrSite site, int count) {
    std::string text;
    try {
        text = downloadSite(site);
    }
    catch (std::exception& e) {
        std::cout << e.what();
        return false;
    }

    std::string ouuRecCnt{ "Recurs lvl: " + std::to_string(count) + ". Site: " + site.url() + "\n" };
    std::cout << ouuRecCnt;

    try {
        indexat.indexation(text, site);
    }
    catch (errorOfTextSite& errText) {
        std::cout << "Error. Not correct code of website page.\n";
        return false;
    }
    catch (std::exception& e) {
        std::cout << "Error of indexation:" << e.what() << std::endl;
        return false;
    }
    return true;
}
