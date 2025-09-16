#pragma once
#include <string>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <vector>

enum class JoinType {
    INNER, LEFT, RIGHT, FULL
};

// exceptoin 
// not understand;  не понимаю, почему
//class valueSql {
//    union V{
//        std::string str_;
//        int i_;
//        V() {}
//        V(std::string s):str_(s){}
//        V(int i):i_(i){}
//        ~V(){}
//    };
//    V val;
//    bool isStr;
//public:
//    valueSql(std::string s) : val(s), isStr(true) {}
//    valueSql(int i): val(i), isStr(false){}
//    ~valueSql() { if (isStr) val.str_.~basic_string/*<char>*/(); }
//    valueSql(const valueSql& oth) { 
//        isStr = oth.isStr;
//        if (isStr)
//            val.str_ = oth.val.str_; // <- exception
//        else val.i_ = oth.val.i_; 
//    }
//    std::string getStr() {
//        if (!isStr) {
//            std::cout << "\nError sql_query! Not string, mast be";
//            std::exit(-1);
//        }
//
//        assert(isStr);
//        return val.str_;
//    }
//    int getInt() {
//        if (isStr) {
//            std::cout << "\nError sql_query! Not string, mast be";
//            std::exit(-1);
//        }
//        assert(!isStr);
//        return val.i_;
//    }
//    bool isString() { return isStr; }
//};
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