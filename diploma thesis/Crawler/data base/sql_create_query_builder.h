#pragma once
#include "sql_query.h"


class SqlCreateQueryBuilder {
protected:
    SqlQuery query;
public:
    SqlCreateQueryBuilder() {}

    SqlCreateQueryBuilder& AddNameTable(std::wstring& name) {        
        query.nameTable = L"CREATE TABLE IF NOT EXISTS "+ name;
        return *this;
    }
    SqlCreateQueryBuilder& AddKey(std::wstring& col) {
        query.column += col + L" SERIAL PRIMARY KEY, ";
        return *this;
    }

    SqlCreateQueryBuilder& AddString(std::wstring& str, int size) {
        query.column += str + L" VARCHAR(" + std::to_wstring(size)+L"), ";
        return *this;
    }

    SqlCreateQueryBuilder& AddStringNN(std::wstring& str, int size) {
        query.column += str + L" VARCHAR(" + std::to_wstring(size) + L") NOT NULL, ";
        return *this;
    }
    
    SqlCreateQueryBuilder& AddReference(std::wstring& name, std::wstring& tbl, std::wstring& col) {
        query.column += name + L" INTEGER NOT NULL REFERENCES " + tbl+L"(" + col + L"), ";
        return *this;
    }

    std::wstring BuildQuery() {
        std::wstring result{};
        if (query.nameTable.empty() || query.column.empty())
            return result;
        result = query.nameTable + L" (" + query.column;
        result.resize(result.size() - 2);
        result += L");";
        return result;
    }
};