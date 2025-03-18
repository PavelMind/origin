#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "myexpect.h"




class ini_parser {
    std::ifstream file;
    
    std::string getSection(std::string& line, int, int);
    void pairRequest(std::string& request, std::string& sect, std::string& var);
    std::string printVariant(std::vector<std::string>&);
    std::string getVar(std::string& line, int start, int num, int& baginval);
    std::string getValue(std::string& line, int start, int numLine);

    template<typename T>
    T readValue(std::string&, int, int) {};
public:
    ini_parser(std::string);
    ~ini_parser();

    template<typename T>
    T get_value(std::string);

    
};



template<>
int ini_parser::readValue<int>(std::string& line, int start, int numLine) {
    auto str = getValue(line, start, numLine);
    int result = std::stoi(str);
    return result;
}

template<>
double ini_parser::readValue<double>(std::string& line, int start, int numLine) {
    auto str = getValue(line, start, numLine);
    double result = std::stod(str);
    return result;
}


#if 3

template<typename T>
T ini_parser::get_value(std::string request) {
    std::string section, var;
    pairRequest(request, section, var);
    
    T result;

    int numLine = 0;
    std::string line;
    bool haveSection = false;
    bool haveValue = false;
    int beginVal = -1;  //начало value
    std::vector<std::string> variantOfVar;

    while (file) {
        ++numLine;
        std::getline(file, line);
        if (line.size() == 0) // пуста€ строка
            continue;
        int firstChar = line.find_first_not_of(" \t");
        if (firstChar == -1) //пробелы  и \t в стоке
            continue;
        if (firstChar == ';') //коментарий
            continue;
        
        if (firstChar == '[' && !haveSection) {
            haveSection = (getSection(line, firstChar, numLine) == section);
            continue;
        }
        if (firstChar == '[' && haveSection) {
            /*if (!haveVar) { // не надо. ¬место этого проверка списка на саиз=0
                printVariant(variantOfVar);
            }*/
            break;
        }
        if (line.find('=', firstChar) == -1)
            throw myexpect(L"Ќекорректный синтаксис!", numLine);

        if (haveSection) {            
            auto nameVar = getVar(line, firstChar, numLine, beginVal);
            if (nameVar != var) {
                variantOfVar.push_back(nameVar);
                continue;
            }
            else {
                result = readValue<T>(line, beginVal, numLine);
                haveValue = true;
                break;
            }
                
        }
        

    }//while
    if (!haveValue) {
        throw std::exception( printVariant(variantOfVar).c_str() );
    }
    return result;

    
}
#endif