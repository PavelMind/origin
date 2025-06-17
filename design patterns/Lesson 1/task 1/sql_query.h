#pragma once
#include <string>


struct SqlQuery
{
    std::string column;
    std::string from;
    std::string where;
    std::string group_by;
    std::string limit;
    std::string having;
    std::string order_by;
};