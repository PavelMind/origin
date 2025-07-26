#pragma once
#include "sql_query.h"
#include <vector>

class SqlSelectQueryBuilder {

    SqlQuery query;
public:
    SqlSelectQueryBuilder(){}
    SqlSelectQueryBuilder& AddColumn(std::wstring& str) {
        if (query.column.empty())
            query.column = str;
        else
            query.column += L", " + str;
        return *this;
    }

    SqlSelectQueryBuilder& AddFrom(std::wstring& str) {
        query.from = L"FROM " + str;
        return *this;
    }

    SqlSelectQueryBuilder& AddWhere(std::wstring& columStr, std::wstring& valueStr) {
        if (query.where.empty())
            query.where = L"WHERE " + columStr + L"=" + valueStr;
        else
            query.where += L" AND " + columStr + L"=" + valueStr;
        return *this;
    }
    

    SqlSelectQueryBuilder& AddColumns(const std::vector<std::wstring>& columns) noexcept {
        for (auto i : columns) {
            if (query.column.empty())
                query.column = i;
            else
                query.column += L", " + i;
        }
        return *this;
    }

    
    SqlSelectQueryBuilder& AddWhere(wchar_t sign, std::wstring& columStr, std::wstring& valueStr) {
        std::wstring signStr{ sign };
        if (sign != '<' && sign != '>') signStr = '=';

        if (query.where.empty())
            query.where = L"WHERE " + columStr + signStr + valueStr;
        else
            query.where += L" AND " + columStr + signStr + valueStr;
        return *this;
    }

    SqlSelectQueryBuilder& AddJoin(JoinType typ, std::wstring& tabl1, std::wstring& c1, 
        std::wstring tabl2, std::wstring c2) 
    {
        std::wstring typJoin;
        switch (typ) {
        case JoinType::INNER: typJoin = L"INNER"; break;
        case JoinType::LEFT: typJoin = L"LEFT"; break;
        case JoinType::RIGHT: typJoin = L"RIGHT"; break;
        case JoinType::FULL: typJoin = L"FULL"; break;
        }
        query.join += typJoin + L" JOIN " + tabl2 + L" ON " 
            + tabl2 + L"." + c2 + L" = " + tabl1 + L"." + c1;
        return *this;
    }

    SqlSelectQueryBuilder& AddJoin(std::wstring& tabl1, std::wstring& c1,
        std::wstring& tabl2, std::wstring& c2)
    {
        AddJoin(JoinType::FULL, tabl1, c1, tabl2, c2);
        return *this;
    }
    
    std::wstring BuildQuery() {
        std::wstring result{};
        if (query.from.empty())
            return result;

        if (query.column.empty())
            result = L"SELECT *";
        else
            result = L"SELECT " + query.column;
        result += L" " + query.from + L" " + query.join + L" " + query.where + L";";
        return result;
    }

};

