#include "parser.h"
#include <iostream>



ini_parser::ini_parser(std::string nameFile) {    
    file.open(nameFile);
    if (!file.is_open())
        throw std::exception("���� �� ������");        
}

ini_parser::~ini_parser() {
    if (file.is_open())
        file.close();
}

void ini_parser::pairRequest(std::string& request, std::string& sect, std::string& var) {
    int point = request.find('.');
    if (point == -1)
        throw std::exception("\n������������ ������\n");

    auto sectTemp = request.substr(0, point);
    auto varTemp = request.substr(point + 1, request.size());

    if (sectTemp.size() == 0 || varTemp.size() == 0)
        throw std::exception("\n������������ ������\n");
    if (request.find('.', point + 1) != -1)    // ������ 1 '.'
        throw std::exception("\n������������ ������\n");

    sect = std::move(sectTemp);
    var = std::move(varTemp);
}

std::string ini_parser::getSection(std::string& line, int start, int numLine) {
    int endSkob = line.find(']', start);
    if ((endSkob - start == 1) || (endSkob == -1))
        throw myexpect(L"������������ ���������!", numLine); // [] ��� ��� ']'

    int beginName = line.find_first_not_of(" \t", start + 1);
    if (beginName == endSkob)
        throw myexpect(L"������������ ���������!", numLine); //��� ��������
    int endName = line.find_last_not_of(" \t", endSkob - 1);

    auto strName = line.substr(beginName, endName - beginName + 1);
    return strName;
}


std::string ini_parser::getVar(std::string& line, int start, int numLine, int& beginValue) {
    int charEquals = line.find('=', start);
    if (charEquals == -1 || charEquals == start)  // ���� '=' ��� ��� �������� ����������
        throw myexpect(L"������������ ���������!", numLine);
    
    int charComment = line.find(';', start);
    if (charComment != -1 && charComment < charEquals)          // ���� ";=..."
        throw myexpect(L"������������ ���������!", numLine);

    int endVar = line.find_last_not_of(" \t", charEquals - 1);

    auto var = line.substr(start, endVar - start + 1);
    beginValue = charEquals + 1;
    
    return var;
}


std::string ini_parser::getValue(std::string& line, int start, int numLine) {
    int beginValue = line.find_first_not_of(" \t", start);
    if (beginValue == -1)
        throw myexpect(L"������������ ���������!", numLine);  //����   ="     "

    int charComment = line.find(';', start);
    int endVal;
    if (charComment != -1 && (charComment == beginValue))
        throw myexpect(L"������������ ���������!", numLine); //����  " ;  comm "

    if (charComment != -1) {
        endVal = line.find_last_not_of(" \t", charComment - 1);
    }
    else {
        endVal = line.find_last_not_of(" \t", line.size() - 1); //���  ="143  \t "
    }
    auto strVal = line.substr(beginValue, endVal - start + 1);
    return strVal;
}

std::string ini_parser::printVariant(std::vector<std::string>& list) {
    std::string str{ "���������� �������� ���. � ������ ���� ����������:\n" };
    for (auto i : list) {
        str = str + i + "\n";
    }
    return str;
}