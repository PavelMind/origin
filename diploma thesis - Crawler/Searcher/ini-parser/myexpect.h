#pragma once
#include <string>

class myexpect {
    std::wstring message;
    int numErrLine;
public:
    myexpect(std::wstring str): message(str), numErrLine(0) {}
    myexpect(std::wstring str, int num) : message(str), numErrLine(num) {}
    std::wstring what() { return message; }
    int numberErrLine() { return numErrLine; }
};
