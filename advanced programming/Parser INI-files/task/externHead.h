#pragma once
#include <utility>
#include <string>

namespace var2 {
    class ini_parser;

    template<typename T>
    T ini_parser::readValue(std::string&) { }

    template<>
    int ini_parser::readValue<int>(std::string& str) {
        int result = std::stoi(str);
        return result;
    }

    template<>
    double ini_parser::readValue<double>(std::string& str) {
        double result = std::stod(str);
        return result;
    }

    template<>
    std::string ini_parser::readValue<std::string>(std::string& str) {
        return str;
    }
}