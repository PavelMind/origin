#pragma once
#include "sql_query.h"


class SqlInsertQueryBuilder {
protected:
    SqlQuery query;
public:
    SqlInsertQueryBuilder() {}

    SqlInsertQueryBuilder& AddNameTable(std::wstring& name) {
        query.nameTable = name;
        return *this;
    }

    SqlInsertQueryBuilder& AddColumn(std::wstring& col, std::wstring& val) {
        query.pairColumns.push_back(col);
        query.pairValues.push_back(val);
        return *this;
    }

    std::wstring BuildQuery() {
        std::wstring result;
        if (query.nameTable.empty())
            return result;

        result = L"INSERT INTO " + query.nameTable + L"(";
        for (auto& i : query.pairColumns) {
            result += i + L", ";
        }
        result.resize(result.size() - 2);
        result += L") VALUES(";
        for (auto& i : query.pairValues) {
            if (i.isString())
                result += L"'" + i.getStr() + L"', ";
            else
                result += i.getInt() + L", ";
        }
        result.resize(result.size() - 2);
        result += L");";
        return result;
    }
};