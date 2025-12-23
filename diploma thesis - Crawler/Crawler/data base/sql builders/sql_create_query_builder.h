#pragma once
#include "sql_query.h"


class SqlCreateQueryBuilder {
protected:
    SqlQuery query;
public:
    SqlCreateQueryBuilder() {}

    SqlCreateQueryBuilder& AddNameTable(std::string name) {        
        query.nameTable = "CREATE TABLE IF NOT EXISTS "+ name;
        return *this;
    }
    SqlCreateQueryBuilder& AddKey(std::string col) {
        query.column += col + " SERIAL PRIMARY KEY, ";
        return *this;
    }
    //-------------
    SqlCreateQueryBuilder& AddString(std::string str, int size) {
        query.column += str + " VARCHAR(" + std::to_string(size)+"), ";
        return *this;
    }

    SqlCreateQueryBuilder& AddStringNN(std::string str, int size) {
        query.column += str + " VARCHAR(" + std::to_string(size) + ") NOT NULL, ";
        return *this;
    }

    SqlCreateQueryBuilder& AddStringUni(std::string str, int size) {
        query.column += str + " VARCHAR(" + std::to_string(size) + ") UNIQUE, ";
        return *this;
    }

    SqlCreateQueryBuilder& AddStringUniNN(std::string str, int size) {
        query.column += str + " VARCHAR(" + std::to_string(size) + ") UNIQUE NOT NULL, ";
        return *this;
    }
    //---------------
    SqlCreateQueryBuilder& AddInt(std::string name) {
        query.column += name + " INTEGER, ";
        return *this;
    }

    SqlCreateQueryBuilder& AddIntNN(std::string name) {
        query.column += name + " INTEGER NOT NULL, ";
        return *this;
    }

    SqlCreateQueryBuilder& AddIntUni(std::string name) {
        query.column += name + " INTEGER UNIQUE, ";
        return *this;
    }

    SqlCreateQueryBuilder& AddIntUniNN(std::string name) {
        query.column += name + " INTEGER UNIQUE NOT NULL, ";
        return *this;
    }
    //--------------
    SqlCreateQueryBuilder& AddReference(std::string name, std::string tbl, std::string col) {
        query.column += name + " INTEGER NOT NULL REFERENCES " + tbl+"(" + col + "), ";
        return *this;
    }

    std::string BuildQuery() {
        std::string result{};
        if (query.nameTable.empty() || query.column.empty())
            return result;
        result = query.nameTable + " (" + query.column;
        result.resize(result.size() - 2);
        result += ");";
        return result;
    }
};