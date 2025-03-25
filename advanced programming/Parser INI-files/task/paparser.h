#pragma once

#include <string>
#include <utility>
#include <map>
#include <fstream>
#include "myexpect.h"
//#include "externHead.h"


namespace var2 {

    class ini_parser {
        using mapVarType = std::map<std::string, std::string>;
        std::map<std::string, mapVarType* > fileData;

        void pairRequest(std::string& request, std::string& sect, std::string& var);
        std::string getSection(std::string& line, size_t, int);
        std::string getVar(std::string& line, size_t start, int num, size_t& baginval);
        std::string getValue(std::string& line, size_t start, int numLine);
        std::string printVariant(mapVarType&);
        bool skip(std::string&, size_t, int);

        void readFile(std::ifstream&);


        template<typename T>
        T readValue(std::string&) ;

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

    /*template<>
    std::string ini_parser::readValue<std::string>(std::string& str) {
        return str;
    }*/

    template<typename T>
    T ini_parser::get_value(std::string request) {
        std::string sectionReq, varReq;
        pairRequest(request, sectionReq, varReq);

        T result;

        auto sect = fileData.find(sectionReq);
        if (sect == fileData.end())
            throw std::exception("Выбранной секции нет");
        if(sect->second==nullptr)
            throw std::exception("В выбранной секции нет переменных");

        mapVarType MapVari = *(sect->second);
        auto var = MapVari.find(varReq);
        if (var == MapVari.end())
            throw std::exception(printVariant(MapVari).c_str());
        else if (var->second.size() == 0)
            throw std::exception("Выбранная переменная не имеет значения");
        else {
            auto val = var->second;
            result = readValue<T>(val);
        }
        return result;
    }



}