#pragma once
#include <iostream>
#include <fstream>
#include <exception>
#include <memory>
#include "logMessage.h"

class programmMustDead :public std::exception {
    const char* str;
public:
    programmMustDead(const char* s):str(s){}
    const char* what() const override {
         return str;
    }
};

class handler {
protected:
    std::unique_ptr<handler> nextHand;
public:
    handler():nextHand(nullptr){}
    virtual void setNextHandler(std::unique_ptr<handler>&& next){
        if (nextHand != nullptr) {
            nextHand->setNextHandler(std::move(next));
        }
        else
            nextHand = std::move(next);
    }
    virtual void processing(LogMessage&){}
};


class handlerWarning : public handler {
public:
    void processing(LogMessage& message) override {
        if (message.type() == Type::warning)
            std::cout << "Warning: " << message.message();
        else if (nextHand != nullptr)
            nextHand->processing(message);
    }
};

class handlerError : public handler {
    std::string nameFile;
public:
    handlerError(std::string name):nameFile(name){}

    void processing(LogMessage& message) override {
        if (message.type() == Type::error)
        {
            std::ofstream fileLog(nameFile, std::ios::app);
            if (!fileLog.is_open())
                return;
            fileLog << "Error: " << message.message() << "\n";
            fileLog.close();
        }
        else if (nextHand != nullptr)
            nextHand->processing(message);
    }
};

class handlerFatalError : public handler {
public:
    void processing(LogMessage& message) override {
        if (message.type() == Type::fatalError)
            throw programmMustDead("Fatal Error!");
        else if (nextHand != nullptr)
            nextHand->processing(message);
    }
};

class handlerUnknown : public handler {
public:
    void processing(LogMessage& message) override {
        if (message.type() == Type::unknown)
            throw std::exception("Not processing message");
        else if (nextHand != nullptr)
            nextHand->processing(message);
    }
};