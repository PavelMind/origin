#include <iostream>
#include "sql_query_builder.h"
#include <cassert>



int main()
{
    SqlSelectQueryBuilder query_builder;
    query_builder.AddColumns(std::vector<std::string> {"name", "phone"});
    query_builder.AddFrom("students");
    std::map<std::string, std::string> wheres;
    wheres["id"] = "42";
    wheres["name"] = "John";
    query_builder.AddWhere(wheres);

    assert(query_builder.BuildQuery() ==
        "SELECT name, phone FROM students WHERE id=42 AND name=John;");




    std::cout << "all are good!";
}
