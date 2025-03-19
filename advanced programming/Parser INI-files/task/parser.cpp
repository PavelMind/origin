#include "parser.h"
#include <iostream>



ini_parser::ini_parser(std::string nameFile) {    
    file.open(nameFile);
    if (!file.is_open())
        throw std::exception("Файл не найден");        
}

ini_parser::~ini_parser() {
    if (file.is_open())
        file.close();
}

void ini_parser::pairRequest(std::string& request, std::string& sect, std::string& var) {
    int point = request.find('.');
    if (point == -1)
        throw std::exception("\nНекорректрый запрос\n");

    auto sectTemp = request.substr(0, point);
    auto varTemp = request.substr(point + 1, request.size());

    if (sectTemp.size() == 0 || varTemp.size() == 0)
        throw std::exception("\nНекорректный запрос\n");
    if (request.find('.', point + 1) != -1)    // больше 1 '.'
        throw std::exception("\nНекорректный запрос\n");

    sect = std::move(sectTemp);
    var = std::move(varTemp);
}

std::string ini_parser::getSection(std::string& line, int start, int numLine) {
    int endSkob = line.find(']', start);
    if ((endSkob - start == 1) || (endSkob == -1))
        throw myexpect(L"Некорректный синтаксис!", numLine); // [] или нет ']'

    int charComment = line.find_first_not_of(" \t", endSkob + 1);
    if (charComment != -1 && line[charComment] != ';')
        throw myexpect(L"Некорректный синтаксис!", numLine); //  [abc] ddd

    int beginName = line.find_first_not_of(" \t", start + 1);
    if (beginName == endSkob)
        throw myexpect(L"Некорректный синтаксис!", numLine); //нет названия
    int endName = line.find_last_not_of(" \t", endSkob - 1);

    auto strName = line.substr(beginName, endName - beginName + 1);
    return strName;
}


std::string ini_parser::getVar(std::string& line, int start, int numLine, int& beginValue) {
    int charEquals = line.find('=', start);
    if (charEquals == -1 || charEquals == start)  // нету '=' или нет названия переменной
        throw myexpect(L"Некорректный синтаксис!", numLine);
    
    int charComment = line.find(';', start);
    if (charComment != -1 && charComment < charEquals)          // если ";=..."
        throw myexpect(L"Некорректный синтаксис!", numLine);

    int endVar = line.find_last_not_of(" \t", charEquals - 1);

    auto var = line.substr(start, endVar - start + 1);
    beginValue = charEquals + 1;
    
    return var;
}


std::string ini_parser::getValue(std::string& line, int start, int numLine) {
    int beginValue = line.find_first_not_of(" \t", start);
    if (beginValue == -1)
        return std::string{};    
        //throw myexpect(L"Некорректный синтаксис!", numLine);  //если   ="     "

    int charComment = line.find(';', start);    
    if (charComment != -1 && (charComment == beginValue))
        throw myexpect(L"Некорректный синтаксис!", numLine); //если  " ;  comm "

    int endVal;
    if (charComment != -1) {
        endVal = line.find_last_not_of(" \t", charComment - 1);
    }
    else {
        endVal = line.find_last_not_of(" \t", line.size() - 1); //для  ="143  \t "
    }
    auto strVal = line.substr(beginValue, endVal - start + 1);
    return strVal;
}

std::string ini_parser::printVariant(std::vector<std::string>& list) {
    std::string str{ "Выбранного варианта нет. В секции есть переменные:\n" };
    for (auto i : list) {
        str = str + i + "\n";
    }
    return str;
}

bool ini_parser::skip(std::string& line, int firstChar, int numLine) {    
    if (line.size() == 0) // пустая строка
        return true;
    if (firstChar == -1) //пробелы  и \t в стоке
        return true;
    if (line[firstChar] == ';') //коментарий
        return true;
    if (line[firstChar] != '[') {
        if (line[firstChar] == '=' || line.find('=', firstChar)==-1)
            throw myexpect(L"Некорректный синтаксис!", numLine);
    }
    return false;
}
