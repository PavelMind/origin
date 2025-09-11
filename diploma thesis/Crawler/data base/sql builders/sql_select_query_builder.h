#pragma once
#include "sql_query.h"
#include <vector>

class SqlSelectQueryBuilder {

    SqlQuery query;
public:
    SqlSelectQueryBuilder(){}
    SqlSelectQueryBuilder& AddColumn(std::string str) {
        if (query.column.empty())
            query.column = str;
        else
            query.column += ", " + str;
        return *this;
    }

    SqlSelectQueryBuilder& AddFrom(std::string str) {
        query.from = "FROM " + str;
        return *this;
    }

    SqlSelectQueryBuilder& AddWhereAnd(std::string columStr, std::string valueStr) {
        if (query.where.empty())
            query.where = "WHERE " + columStr + "=\'" + valueStr + "\'";
        else
            query.where += " AND " + columStr + "=\'" + valueStr + "\'";
        return *this;
    }

    SqlSelectQueryBuilder& AddWhereOr(std::string columStr, std::string valueStr) {
        if (query.where.empty())
            query.where = "WHERE " + columStr + "=\'" + valueStr + "\'";
        else
            query.where += " OR " + columStr + "=\'" + valueStr + "\'";
        return *this;
    }

    SqlSelectQueryBuilder& AddWhereAnd(std::string columStr, int valueStr) {
        if (query.where.empty())
            query.where = "WHERE " + columStr + "=" + std::to_string(valueStr);
        else
            query.where += " AND " + columStr + "=" + std::to_string(valueStr);
        return *this;
    }

    SqlSelectQueryBuilder& AddWhereOr(std::string columStr, int valueStr) {
        if (query.where.empty())
            query.where = "WHERE " + columStr + "=" + std::to_string(valueStr);
        else
            query.where += " OR " + columStr + "=" + std::to_string(valueStr);
        return *this;
    }
    
    SqlSelectQueryBuilder& AddWhereAnd(char sign, std::string columStr, std::string valueStr) {
        std::string signStr{ sign };
        if (sign != '<' && sign != '>') signStr = '=';

        if (query.where.empty())
            query.where = "WHERE " + columStr + signStr + valueStr;
        else
            query.where += " AND " + columStr + signStr + valueStr;
        return *this;
    }

    SqlSelectQueryBuilder& AddJoin(JoinType typ, std::string tabl1, std::string c1, 
        std::string tabl2, std::string c2) 
    {
        std::string typJoin;
        switch (typ) {
        case JoinType::INNER: typJoin = "INNER"; break;
        case JoinType::LEFT: typJoin = "LEFT"; break;
        case JoinType::RIGHT: typJoin = "RIGHT"; break;
        case JoinType::FULL: typJoin = "FULL"; break;
        }
        query.join += " " + typJoin + " JOIN " + tabl2 + " ON "
            + tabl2 + "." + c2 + " = " + tabl1 + "." + c1;
        return *this;
    }

    SqlSelectQueryBuilder& AddJoin(std::string tabl1, std::string c1,
        std::string tabl2, std::string c2)
    {
        AddJoin(JoinType::FULL, tabl1, c1, tabl2, c2);
        return *this;
    }
    
    SqlSelectQueryBuilder& AddGroupBy(std::string str) {
        if (query.group_by.empty())
            query.group_by = "GROUP BY " + str;
        else
            query.group_by += ", " + str;
        return *this;
    }

    SqlSelectQueryBuilder& AddOrderByDesc(std::string str) {
        if (query.order_by.empty())
            query.order_by = "ORDER BY " + str + " DESC";
        else
            query.order_by += ", " + str + " DESC";
        return *this;
    }

    SqlSelectQueryBuilder& AddOrderByAsc(std::string str) {
        if (query.order_by.empty())
            query.order_by = "ORDER BY " + str + " ASC";
        else
            query.order_by += ", " + str + " ASC";
        return *this;
    }

    SqlSelectQueryBuilder& AddLimit(std::string str) {
        query.limit = "LIMIT " + str;
        return *this;
    }

    std::string BuildQuery() {
        std::string result{};
        if (query.from.empty())
            return result;

        if (query.column.empty())
            return result;
        else
            result = "SELECT " + query.column;
        result += " " + query.from + " " + query.join + " " + query.where + " " +
            query.group_by + " " + query.order_by + " " + query.limit + ";";
        return result;
    }

};

