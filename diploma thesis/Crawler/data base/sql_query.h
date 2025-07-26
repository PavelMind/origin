#pragma once
#include <string>
#include <vector>

enum class JoinType {
    INNER, LEFT, RIGHT, FULL
};

class valueSql {
    union {
        std::wstring str_;
        int i_;
    };
    bool isStr;
public:
    valueSql(std::wstring s) : str_(s), isStr(true) {}
    valueSql(int i): i_(i), isStr(false){}
    ~valueSql() { if (isStr) str_.~basic_string/*<wchar_t>*/(); }
    valueSql(const valueSql& oth) { if (isStr)str_ = oth.str_; else i_ = oth.i_; }
    std::wstring getStr() {
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
    std::wstring nameTable;

    std::vector<std::wstring> pairColumns;
    std::vector<valueSql> pairValues;

    std::wstring column;
    std::wstring from;
    std::wstring where;
    std::wstring join;

};