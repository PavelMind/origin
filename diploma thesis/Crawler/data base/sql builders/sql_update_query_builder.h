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

    SqlUpdateQueryBuilder& AddColumn(std::string col, std::string val) {
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

    SqlUpdateQueryBuilder& AddWhere(std::string columStr, std::string valueStr) {
        if (query.where.empty())
            query.where = "WHERE " + columStr + "=" + valueStr;
        else
            query.where += " AND " + columStr + "=" + valueStr;
        return *this;
    }

    std::string BuildQuery() {
        if (query.where.empty())
            return std::string{};
        return BuildQueryFullT();
    }

    std::string BuildQueryFullT() {
        std::string result;
        if (query.nameTable.empty() || query.pairColumns.empty())
            return result;

        result = "UPDATE " + query.nameTable + " SET ";
        int count = query.pairValues.size();
        for (int i = 0; i < count; ++i) {
            result += query.pairColumns[i] + " = ";            
            if(query.pairValues[i].isString())
                result += "'" + query.pairValues[i].getStr() + "', ";
            else
                result += query.pairValues[i].getInt() + ", ";
        }

        result.resize(result.size() - 2);
        result += query.where + ";";
        return result;
    }
};