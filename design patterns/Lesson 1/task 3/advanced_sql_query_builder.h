#pragma once
#include "sql_query_builder.h"

class AdvancedSqlSelectQueryBuilder : public SqlSelectQueryBuilder {

public:
    AdvancedSqlSelectQueryBuilder& AddWhere(char sign, std::string columStr, std::string valueStr) {
        std::string signStr{ sign };
        if (sign != '<' && sign != '>') signStr = '=';

        if (query.where.empty())
            query.where = "WHERE " + columStr + signStr + valueStr;
        else
            query.where += " AND " + columStr + signStr + valueStr;
        return *this;
    }
};