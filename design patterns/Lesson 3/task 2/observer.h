#pragma once
#include <iostream>
#include <fstream>
#include <string>
//#include "observable.h"
//class Observer;

class observable;
//void observable::removeObserver(Observer*);

class Observer {
    
public:    
    virtual ~Observer() = default;
    virtual void onWarning(const std::string& message) {}
    virtual void onError(const std::string& message) {}
    virtual void onFatalError(const std::string& message) {}
};



class warningObserver:public Observer {
public:
    void onWarning(const std::string& message) override {
        std::cout << "Warning: " << message << std::endl;
    }
};

class errorObserver: public Observer {
    std::string nameFile;
public:
    errorObserver(std::string name) :nameFile(name) {}
    void onError(const std::string& message) override {
        std::ofstream fileLog(nameFile, std::ios::app);
        if (!fileLog.is_open())
            return;
        fileLog << "Error: " << message << "\n";
        fileLog.close();
    }
};

class fatalErrorObserver: public Observer {
    std::string nameFile;
public:
    fatalErrorObserver(std::string name) :nameFile(name) {}
    void onFatalError(const std::string& message) override {
        std::cout << "FatalError: " << message << std::endl;

        std::ofstream fileLog(nameFile, std::ios::app);
        if (!fileLog.is_open())
            return;
        fileLog << "Fatal: " << message << "\n";
        fileLog.close();
    }
};