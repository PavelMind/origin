#include "listLinks.h"


std::vector<addrSite>&& listLinks::getLinks() {
    std::lock_guard<std::mutex> m{ mutL };
    return std::move(links);
}

void listLinks::push(addrSite& addr) {
    std::lock_guard<std::mutex> m{ mutL };
    links.push_back(addr);
}

bool listLinks::isProcAndMarked(addrSite& addr) {
    std::lock_guard<std::mutex> m{ mutP };
    if (processed.find(addr) == processed.end()) {
        processed.insert(addr);
        return false;
    }
    else
        return true;
}

bool listLinks::empty() {
    std::lock_guard<std::mutex> m{ mutL };
    return links.empty();
}