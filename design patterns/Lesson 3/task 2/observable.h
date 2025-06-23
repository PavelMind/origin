#pragma once
#include <vector>
#include <algorithm>
#include "observer.h"
//class Observer;

class observable {
protected:
    std::vector<Observer*> vecObservers;
    std::string str;
public:
    observable() {
        str.resize(10);
    }
    observable& addObserver(Observer* obs) {
        if (std::find(vecObservers.begin(), vecObservers.end(), obs) == vecObservers.end()) {
            vecObservers.push_back(obs);
        }
        return *this;
    }
    void removeObserver(Observer* obs) {
        auto deleted = std::find(vecObservers.begin(), vecObservers.end(), obs);
        if (deleted != vecObservers.end()) {
            std::swap(*deleted, *(vecObservers.end() - 1));
            vecObservers.erase(deleted, vecObservers.end());
        }
    }

    void setString(const std::string message) {
        if (message.size() > 10) {
            fatalError("size exceeded!");
            return;
        }
        if (message.empty()) {
            error("No message!");
            return;
        }
        if (message.size() < 3)
            warning("Small size");
        str = message;
    }

    void warning(const std::string& message) const {
        for (auto i : vecObservers) {
            i->onWarning(message);
        }

    }
    void error(const std::string& message) const {
        for (auto i : vecObservers) {
            i->onError(message);
        }
    }
    void fatalError(const std::string& message) const {
        for (auto i : vecObservers) {
            i->onFatalError(message);
        }
    }
};