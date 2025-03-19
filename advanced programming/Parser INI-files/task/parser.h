#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "myexpect.h"




class ini_parser {
    std::ifstream file;

    void pairRequest(std::string& request, std::string& sect, std::string& var);
    std::string getSection(std::string& line, int, int);   
    std::string getVar(std::string& line, int start, int num, int& baginval);
    std::string getValue(std::string& line, int start, int numLine);
    std::string printVariant(std::vector<std::string>&);
    bool skip(std::string&, int,int);

    template<typename T>
    T readValue(std::string&) { };

    template<>
    int readValue<int>(std::string& str) {        
        int result = std::stoi(str);
        return result;
    }

    template<>
    double readValue<double>(std::string& str) {         
        double result = std::stod(str);
        return result;
    }

    template<>
    std::string readValue<std::string>(std::string& str) {                
        return str;
    }
public:
    ini_parser(std::string);
    ~ini_parser();

    template<typename T>
    T get_value(std::string);
    
};




#if 3

template<typename T>
T ini_parser::get_value(std::string request) {
    std::string section, var;
    pairRequest(request, section, var);
    
    T result;

    int numLine = 0;
    std::string line;
    bool inNeedSection = false;
    bool haveSection = false;
    bool haveVar = false;
    bool haveValue = false;
    int beginValue = -1;  //начало value
    std::vector<std::string> variantOfVar;

    while (file) {
        ++numLine;
        std::getline(file, line);
        int firstChar = line.find_first_not_of(" \t");
        if (skip(line, firstChar, numLine))
            continue;
                
        if(line[firstChar] == '[') {
            inNeedSection = (getSection(line, firstChar, numLine) == section);
            if (inNeedSection)
                haveSection = true;
            continue;
        }

        if (inNeedSection) {            
            auto nameVar = getVar(line, firstChar, numLine, beginValue);
            if (nameVar != var) {
                variantOfVar.push_back(nameVar);
                continue;
            }
            else {
                haveVar = true;
                std::string str = getValue(line, beginValue, numLine);
                if (str.empty()) {
                    continue;
                }
                result = readValue<T>(str);
                haveValue = true;
                continue;
            }
                
        }
        
    }//while

    if (!haveSection) {
        throw std::exception("Выбранной секции нет");
    }
    if (!haveValue && variantOfVar.empty()) {
        throw std::exception("В выбранной секции нет переменных");
    }

    if (!haveVar) {// если не найдено переменной var
        throw std::exception( printVariant(variantOfVar).c_str() );
    }
    if (haveVar && !haveValue) {
        throw std::exception("Переменная не имеет значения");
    }
    return result;       
}
#endif