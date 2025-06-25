#pragma once
#include <fstream>


class PrintTypeI {
public:
    virtual ~PrintTypeI() = default;
    virtual std::string print(std::string&) const = 0;
};

class printAsHTML :public PrintTypeI {
public:
    std::string print(std::string& str) const override
    {
        return "<html>" + str + "<html/>";
    }
};

class printAsText :public PrintTypeI {
public:
    std::string print(std::string& str) const override
    {
        return str;
    }
};

class printAsJSON :public PrintTypeI {
public:
    std::string print(std::string& str) const override
    {
        return "{ \"data\": \"" + str + "\"}";
    }
};

class dataPrintableInt
{
public:
    virtual ~dataPrintableInt() = default;
    virtual std::string print(PrintTypeI*) = 0;
};

class Data : public dataPrintableInt
{
public:
    Data(std::string data) : data_(std::move(data)) {}
    std::string print(PrintTypeI* typePrint) override {
        return typePrint->print(data_);
    }
    
private:
    std::string data_;
};



void saveTo(std::ofstream& file, dataPrintableInt* printable, PrintTypeI* pType)
{
    file << printable->print(pType)<<"\n";
}

void saveToAsHTML(std::ofstream& file,  dataPrintableInt* printable) {
    PrintTypeI* pTyp = new printAsHTML;
    saveTo(file, printable, pTyp);
    delete pTyp;
}

void saveToAsJSON(std::ofstream& file, dataPrintableInt* printable) {
    PrintTypeI* pTyp = new printAsJSON;
    saveTo(file, printable, pTyp);
    delete pTyp;
}

void saveToAsText(std::ofstream& file, dataPrintableInt* printable) {
    PrintTypeI* pTyp = new printAsText;
    saveTo(file, printable, pTyp);
    delete pTyp;
}