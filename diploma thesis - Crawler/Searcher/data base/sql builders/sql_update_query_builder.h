#pragma once
#include "sql_query.h"


class SqlUpdateQueryBuilder {
protected:
    SqlQuery query;
public:
    SqlUpdateQueryBuilder() { }

    SqlUpdateQueryBuilder& AddNameTable(std::string name) {
        query.nameTable = name;
        return *this;
    }

    SqlUpdateQueryBuilder& AddColumnValue(std::string col, std::string val) {
        query.pairColumns.push_back(col);
        query.pairValues.push_back(val);
        return *this;
    }

    SqlUpdateQueryBuilder& AddColumnValue(std::string col, int val) {
        query.pairColumns.push_back(col);
        query.pairValues.push_back(val);
        return *this;
    }

    SqlUpdateQueryBuilder& AddWhere(char sign, std::string columStr, std::string valueStr) {
        std::string signStr{ sign };
        if (sign != '<' && sign != '>') signStr = '=';

        if (query.where.empty())
            query.where = "WHERE " + columStr + signStr + valueStr;
        else
            query.where += " AND " + columStr + signStr + valueStr;
        return *this;
    }

    SqlUpdateQueryBuilder& AddWhereAnd(std::string columStr, std::string valueStr) {
        if (query.where.empty())
            query.where = "WHERE " + columStr + "=" + valueStr;
        else
            query.where += " AND " + columStr + "=" + valueStr;
        return *this;
    }

    SqlUpdateQueryBuilder& AddWhereAnd(std::string columStr, int valueStr) {
        if (query.where.empty())
            query.where = "WHERE " + columStr + "=" + std::to_string(valueStr);
        else
            query.where += " AND " + columStr + "=" + std::to_string(valueStr);
        return *this;
    }

    SqlUpdateQueryBuilder& AddWhereOr(std::string columStr, std::string valueStr) {
        if (query.where.empty())
            query.where = "WHERE " + columStr + "=" + valueStr;
        else
            query.where += " OR " + columStr + "=" + valueStr;
        return *this;
    }

    SqlUpdateQueryBuilder& AddWhereOr(std::string columStr, int valueStr) {
        if (query.where.empty())
            query.where = "WHERE " + columStr + "=" + std::to_string(valueStr);
        else
            query.where += " OR " + columStr + "=" + std::to_string(valueStr);
        return *this;
    }

    std::string BuildQuery() {
        if (query.where.empty())
            return std::string{};
        return BuildQueryFullTable(true);
    }

    std::string BuildQueryFullTable(bool yes) {
        std::string result;
        if (!yes) return result;
        if (query.nameTable.empty() || query.pairColumns.empty())
            return result;

        result = "UPDATE " + query.nameTable + " SET ";
        int count = query.pairValues.size();
        for (int i = 0; i < count; ++i) {
            result += query.pairColumns[i] + " = ";            
            if(query.pairValues[i].isString())
                result += "'" + query.pairValues[i].getStr() + "', ";
            else {
                int tmp = query.pairValues[i].getInt();
                result += std::to_string(tmp) + ", ";
            }                
        }

        result.resize(result.size() - 2);
        result += " " + query.where + ";";
        return result;
    }
};