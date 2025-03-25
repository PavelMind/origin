#include "paparser.h" 

namespace var2 {

    ini_parser::ini_parser(std::string name) {
        std::ifstream file(name);
        if(!file.is_open())
            throw std::exception("���� �� ������");
        readFile(file);
        file.close();
    }

    ini_parser::~ini_parser() {
        for (auto i : fileData) {
            if (i.second != nullptr)
                delete i.second;
        }
    }

    void ini_parser::readFile(std::ifstream& file) {
        int numLine = 0;
        std::string line;
        bool inSection = false;        
        size_t beginValue = 0;  //������ value        
        std::string currSection;

        while (file) {
            ++numLine;
            std::getline(file, line);
            size_t firstChar = line.find_first_not_of(" \t");
            if (skip(line, firstChar, numLine))
                continue;

            if (line[firstChar] == '[') {
                currSection = getSection(line, firstChar, numLine);
                if (fileData.find(currSection) == fileData.end()) {
                    fileData[currSection] = nullptr;
                }
                inSection = true;
                continue;
            }

            if (inSection) {
                std::string nameVar = getVar(line, firstChar, numLine, beginValue);
                std::string strVal = getValue(line, beginValue, numLine);
                auto itSection = fileData.find(currSection);
                if (itSection->second==nullptr) {  
                    //mapVarType* p = itSection->second;                    
                    //p = new mapVarType;
                    //p->insert({ nameVar,strVal });
                    itSection->second = new mapVarType;
                    itSection->second->insert_or_assign( nameVar,strVal );
                }
                else {
                    //mapVarType* p = itSection->second;
                    //p->insert({ nameVar,strVal });
                    itSection->second->insert_or_assign( nameVar,strVal );
                }

                continue;
            }

        }
    }

    std::string ini_parser::getSection(std::string& line, size_t start, int numLine) {
        auto endSkob = line.find(']', start);
        if ((endSkob - start == 1) || (endSkob == -1))
            throw myexpect(L"������������ ���������!", numLine); // [] ��� ��� ']'

        auto charComment = line.find_first_not_of(" \t", endSkob + 1);
        if (charComment != -1 && line[charComment] != ';')
            throw myexpect(L"������������ ���������!", numLine); //  [abc] ddd

        auto beginName = line.find_first_not_of(" \t", start + 1);
        if (beginName == endSkob)
            throw myexpect(L"������������ ���������!", numLine); //��� ��������
        auto endName = line.find_last_not_of(" \t", endSkob - 1);

        auto strName = line.substr(beginName, endName - beginName + 1);
        return strName;
    }

    std::string ini_parser::getVar(std::string& line, size_t start, int numLine, size_t& beginValue) {
        auto charEquals = line.find('=', start);
        if (charEquals == -1 || charEquals == start)  // ���� '=' ��� ��� �������� ����������
            throw myexpect(L"������������ ���������!", numLine);

        auto charComment = line.find(';', start);
        if (charComment != -1 && charComment < charEquals)          // ���� "vr ;=..."
            throw myexpect(L"������������ ���������!", numLine);

        auto endVar = line.find_last_not_of(" \t", charEquals - 1);

        auto var = line.substr(start, endVar - start + 1);
        beginValue = charEquals + 1;

        return var;
    }

    std::string ini_parser::getValue(std::string& line, size_t start, int numLine) {
        auto beginValue = line.find_first_not_of(" \t", start);
        if (beginValue == -1)
            return std::string{};

        auto charComment = line.find(';', start);
        if (charComment != -1 && (charComment == beginValue))
            throw myexpect(L"������������ ���������!", numLine); //����  " ;  comm "

        size_t endVal;
        if (charComment != -1) {
            endVal = line.find_last_not_of(" \t", charComment - 1);
        }
        else {
            endVal = line.find_last_not_of(" \t", line.size() - 1); //���  ="143  \t "
        }
        auto strVal = line.substr(beginValue, endVal - start + 1);
        return strVal;
    }

    bool ini_parser::skip(std::string& line, size_t firstChar, int numLine) {
        if (line.size() == 0) // ������ ������
            return true;
        if (firstChar == -1) //�������  � \t � �����
            return true;
        if (line[firstChar] == ';') //����������
            return true;
        if (line[firstChar] != '[') {
            if (line[firstChar] == '=' || line.find('=', firstChar) == -1)
                throw myexpect(L"������������ ���������!", numLine);
        }
        return false;
    }

    void ini_parser::pairRequest(std::string& request, std::string& sect, std::string& var) {
        auto point = request.find('.');
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

    std::string ini_parser::printVariant(mapVarType& list) {
        std::string str{ "���������� �������� ���. � ������ ���� ����������:\n" };
        for (auto i : list) {
            auto var = i.first;
            str = str + var + "\n";
        }
        return str;
    }



}