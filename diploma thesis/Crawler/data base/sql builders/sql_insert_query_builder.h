#pragma once
#include "sql_query.h"


class SqlInsertQueryBuilder {
protected:
    SqlQuery query;
public:
    SqlInsertQueryBuilder() {}

    SqlInsertQueryBuilder& AddNameTable(std::string name) {
        query.nameTable = name;
        return *this;
    }

    SqlInsertQueryBuilder& AddColumn(std::string col, std::string val) {
        query.pairColumns.push_back(col);
        query.pairValues.push_back(val);
        return *this;
    }

    std::string BuildQuery() {
        std::string result;
        if (query.nameTable.empty())
            return result;

        result = "INSERT INTO " + query.nameTable + "(";
        for (auto& i : query.pairColumns) {
            result += i + ", ";
        }
        result.resize(result.size() - 2);
        result += ") VALUES(";
        for (auto& i : query.pairValues) {
            if (i.isString())
                result += "'" + i.getStr() + "', ";
            else
                result += i.getInt() + ", ";
        }
        result.resize(result.size() - 2);
        result += ");";
        return result;
    }
};