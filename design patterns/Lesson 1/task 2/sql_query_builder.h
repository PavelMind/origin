#pragma once
#include "sql_query.h"
#include <map>
#include <vector>

class SqlSelectQueryBuilder {
protected:
    SqlQuery query;
public:
    SqlSelectQueryBuilder(){}
    SqlSelectQueryBuilder& AddColumn(std::string str) {
        if (query.column.empty())
            query.column = "SELECT " + str;
        else
            query.column += ", " + str;
        return *this;
    }

    SqlSelectQueryBuilder& AddFrom(std::string str) {
        query.from = "FROM " + str;
        return *this;
    }

    SqlSelectQueryBuilder& AddWhere(std::string columStr, std::string valueStr) {
        if (query.where.empty())
            query.where = "WHERE " + columStr + "=" + valueStr;
        else
            query.where += " AND " + columStr + "=" + valueStr;
        return *this;
    }

    SqlSelectQueryBuilder& AddWhere(const std::map<std::string, std::string>& mp) noexcept {
        for (auto i: mp) {
            if (query.where.empty())
                query.where = "WHERE " + i.first + "=" + i.second;
            else
                query.where += " AND " + i.first + "=" + i.second;
        }
        return *this;
    }

    SqlSelectQueryBuilder& AddColumns(const std::vector<std::string>& columns) noexcept {
        for (auto i : columns) {
            if (query.column.empty())
                query.column = "SELECT " + i;
            else
                query.column += ", " + i;
        }
        return *this;
    }

    std::string BuildQuery() {
        std::string result{};
        if (query.from.empty())
            return result;

        if (query.column.empty())
            result = "SELECT *";
        else
            result = query.column;
        result += " " + query.from + " " + query.where + ";";
        return result;
    }

};

