#pragma once
#include <pqxx/pqxx>
#include <string>
#include <vector>


struct DBinfoClient{
        int id;
        std::string first_name;
        std::string last_name;
        std::string email;
        std::string number;
};

class DBclass {
    pqxx::connection conn;
public:
    DBclass();
    ~DBclass();

    void create();
    int addClient(std::string, std::string, std::string);
    void addPhone(int, std::string);
    std::vector<DBinfoClient> get(std::string, std::string, std::string, std::string);
    void updateClient(int, std::string, std::string, std::string);
    void deleteClient(int);
    void deletePhone(std::string);
    void cleanedTable();
};