#include <iostream>
#include <pqxx/pqxx>
#include "DBclass.h"
#include <string>
 

int main() {
    setlocale(LC_ALL, "Russian");
    try {
        DBclass db;
        db.create();

        db.addClient("Вясян", "Пупкин", "vasa@mail.ru");
        auto tempVec = db.get("Васян", "", "", "");
        db.addPhone(tempVec[0].id, "89002004477");

        int tempInt = db.addClient("Алёна", "Свиридова", "alona@gmail.com");
        db.addPhone(tempInt, "+79001002233");
        db.addPhone(tempInt, "88007770011");

        tempVec = db.get("", "", "", "88007770011");
        std::cout << "get 88007770011\n";
        for (auto i : tempVec) {
            std::cout << i.id << " " << i.first_name << " " << i.last_name << " " << i.email << " " << i.number << "\n";
        }

        db.updateClient(tempInt, "", "Луккезе", "");
        tempVec = db.get("Алёна", "", "", "");
        std::cout << "\nпосле update\n";
        for (auto i : tempVec) {
            std::cout << i.id << " " << i.first_name << " " << i.last_name << " " << i.email << " " << i.number << "\n";
        }

        db.deletePhone("+79001002233");
        tempVec = db.get("Алёна", "", "", "");
        std::cout << "\nпосле deletePhone алёны\n";
        for (auto i : tempVec) {
            std::cout << i.id << " " << i.first_name << " " << i.last_name << " " << i.email << " " << i.number << "\n";
        }

        tempVec = db.get("Васян", "", "", "");
        db.addPhone(tempVec[0].id, "81009001199");
        std::cout << "\nпосле addPhone Васи\n";
        for (auto i : tempVec) {
            std::cout << i.id << " " << i.first_name << " " << i.last_name << " " << i.email << " " << i.number << "\n";
        }

        db.deleteClient(tempVec[0].id);
        tempVec = db.get("Васян", "", "", "");
        std::cout << "\nпосле deleteClient Васяна\n";
        for (auto i : tempVec) {
            std::cout << i.id << " " << i.first_name << " " << i.last_name << " " << i.email << " " << i.number << "\n";
        }

        db.addPhone(666, "431100");
        db.get("", "", "", "");

    }
    catch (pqxx::sql_error erPQXX) {
        std::cout << erPQXX.what() << std::endl;
    }
    catch (std::exception e) {
        std::cout << e.what() << std::endl;
    }


}