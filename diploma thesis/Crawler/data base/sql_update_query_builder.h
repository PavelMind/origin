#pragma once
#include "sql_query.h"


class SqlUpdateQueryBuilder {
protected:
    SqlQuery query;
public:
    SqlUpdateQueryBuilder() { }

    SqlUpdateQueryBuilder& AddNameTable(std::wstring& name) {
        query.nameTable = name;
        return *this;
    }

    SqlUpdateQueryBuilder& AddColumn(std::wstring& col, std::wstring& val) {
        query.pairColumns.push_back(col);
        query.pairValues.push_back(val);
        return *this;
    }

    SqlUpdateQueryBuilder& AddWhere(wchar_t sign, std::wstring& columStr, std::wstring& valueStr) {
        std::wstring signStr{ sign };
        if (sign != '<' && sign != '>') signStr = '=';

        if (query.where.empty())
            query.where = L"WHERE " + columStr + signStr + valueStr;
        else
            query.where += L" AND " + columStr + signStr + valueStr;
        return *this;
    }

    SqlUpdateQueryBuilder& AddWhere(std::wstring& columStr, std::wstring& valueStr) {
        if (query.where.empty())
            query.where = L"WHERE " + columStr + L"=" + valueStr;
        else
            query.where += L" AND " + columStr + L"=" + valueStr;
        return *this;
    }

    std::wstring BuildQuery() {
        if (query.where.empty())
            return std::wstring{};
        return BuildQueryFullT();
    }

    std::wstring BuildQueryFullT() {
        std::wstring result;
        if (query.nameTable.empty() || query.pairColumns.empty())
            return result;

        result = L"UPDATE " + query.nameTable + L" SET ";
        int count = query.pairValues.size();
        for (int i = 0; i < count; ++i) {
            result += query.pairColumns[i] + L" = ";            
            if(query.pairValues[i].isString())
                result += L"'" + query.pairValues[i].getStr() + L"', ";
            else
                result += query.pairValues[i].getInt() + L", ";
        }

        result.resize(result.size() - 2);
        result += query.where + L";";
        return result;
    }
};