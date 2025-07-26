#pragma once
#include "sql_query.h"


class SqlDeleteQueryBuilder {
protected:
    SqlQuery query;
public:
    SqlDeleteQueryBuilder() {}

    SqlDeleteQueryBuilder& AddNameTable(std::wstring& name) {
        query.nameTable = name;
        return *this;
    }


    SqlDeleteQueryBuilder& AddWhere(wchar_t sign, std::wstring& columStr, std::wstring& valueStr) {
        std::wstring signStr{ sign };
        if (sign != '<' && sign != '>') signStr = '=';

        if (query.where.empty())
            query.where = L"WHERE " + columStr + signStr + valueStr;
        else
            query.where += L" AND " + columStr + signStr + valueStr;
        return *this;
    }

    SqlDeleteQueryBuilder& AddWhere(std::wstring& columStr, std::wstring& valueStr) {
        if (query.where.empty())
            query.where = L"WHERE " + columStr + L"=" + valueStr;
        else
            query.where += L" AND " + columStr + L"=" + valueStr;
        return *this;
    }

    std::wstring BuildQuery() {
        if (query.where.empty())
            return std::wstring();
        return BuildQueryFullT();
    }

    std::wstring BuildQueryFullT() {
        std::wstring result;
        if (query.nameTable.empty())
            return result;
        result = L"DELETE FROM " + query.nameTable + L" " + query.where + L";";
        return result;
    }
};