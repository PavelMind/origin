#pragma once
#include "sql_query.h"


class SqlDeleteQueryBuilder {
protected:
    SqlQuery query;
public:
    SqlDeleteQueryBuilder() {}

    SqlDeleteQueryBuilder& AddNameTable(std::string name) {
        query.nameTable = name;
        return *this;
    }


    SqlDeleteQueryBuilder& AddWhere(char sign, std::string columStr, std::string valueStr) {
        std::string signStr{ sign };
        if (sign != '<' && sign != '>') signStr = '=';

        if (query.where.empty())
            query.where = "WHERE " + columStr + signStr + valueStr;
        else
            query.where += " AND " + columStr + signStr + valueStr;
        return *this;
    }

    SqlDeleteQueryBuilder& AddWhere(std::string columStr, std::string valueStr) {
        if (query.where.empty())
            query.where = "WHERE " + columStr + "=" + valueStr;
        else
            query.where += " AND " + columStr + "=" + valueStr;
        return *this;
    }

    std::string BuildQuery() {
        if (query.where.empty())
            return std::string();
        return BuildQueryFullT();
    }

    std::string BuildQueryFullT() {
        std::string result;
        if (query.nameTable.empty())
            return result;
        result = "DELETE FROM " + query.nameTable + " " + query.where + ";";
        return result;
    }
};