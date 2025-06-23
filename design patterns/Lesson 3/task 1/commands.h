#pragma once
#include <string>
#include <iostream>
#include <fstream>


class LogCommand {
public:
    virtual ~LogCommand() = default;
    virtual void print(const std::string& message) = 0;
};

class consolLogCommand : public LogCommand {
public:
    void print(const std::string& massage) override {
        std::cout << massage << std::endl;
    }
};

class fileLogCommand : public LogCommand {
public:
    void print(const std::string& massage) override {
        std::ofstream fileLog("log.txt", std::ios::app);
        if (!fileLog.is_open())
            return;
        fileLog << massage<<"| ";
        fileLog.close();
    }
};

void print(LogCommand* command, std::string massage) {
    command->print(massage);
}