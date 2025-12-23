#pragma once
#include <string>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <vector>

enum class JoinType {
    INNER, LEFT, RIGHT, FULL
};

class valueSql {
    std::string strV;
    int intV;
    bool isStr;
public:
    valueSql(std::string s) : strV(s), isStr(true) {}
    valueSql(int i) : intV(i), isStr(false) {}
    ~valueSql() {}
    valueSql(const valueSql& oth) = default;
    std::string getStr() {
        if (!isStr) {
            std::cout << "\nError sql_query! Not string, mast be";
            std::exit(-1);
        }
        return strV;
    }
    int getInt() {
        if (isStr) {
            std::cout << "\nError sql_query! Not string, mast be";
            std::exit(-1);
        }
        return intV;
    }
    bool isString() { return isStr; }
};

struct SqlQuery
{
    std::string nameTable;

    std::vector<std::string> pairColumns;
    std::vector<valueSql> pairValues;

    std::string column;
    std::string from;
    std::string where;
    std::string join;
    std::string group_by;
    std::string order_by;
    std::string limit;
};