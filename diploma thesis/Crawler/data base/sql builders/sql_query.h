#pragma once
#include <string>
#include <cassert>
#include <vector>

enum class JoinType {
    INNER, LEFT, RIGHT, FULL
};

class valueSql {
    union {
        std::string str_;
        int i_;
    };
    bool isStr;
public:
    valueSql(std::string s) : str_(s), isStr(true) {}
    valueSql(int i): i_(i), isStr(false){}
    ~valueSql() { if (isStr) str_.~basic_string/*<wchar_t>*/(); }
    valueSql(const valueSql& oth) { 
        isStr = oth.isStr;
        if (isStr)
            str_ = oth.str_; 
        else i_ = oth.i_; 
    }
    std::string getStr() {
        assert(isStr);
        return str_;
    }
    int getInt() {
        assert(!isStr);
        return i_;
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