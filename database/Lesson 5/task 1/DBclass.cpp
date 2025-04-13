#include "DBclass.h"

DBclass::DBclass() {
        pqxx::connection c(
            "host=localhost "
            "port=5432 "
            "dbname=my_database "
            "user=my_database_user "
            "password=my_password_123");
        conn = std::move(c);
    }

DBclass::~DBclass(){}

void DBclass::create() {
    pqxx::work tr{ conn };
    tr.exec("CREATE TABLE Clients(\
            id SERIAL PRIMARY KEY,\
            first_name VARCHAR(20) NOT NULL,\
            last_name VARCHAR(20) NOT NULL,\
            email VARCHAR(30) NOT NULL");

    tr.exec("CREATE TABLE phoneNumber (\
            id SERIAL PRIMARY KEY,\
            client_id INTEGER NOT NULL REFERENCES Clients(id),\
            number VARCHAR(13) NOT NULL); ");
    tr.commit();
}

int DBclass::addClient(std::string name, std::string famil, std::string mail) {
    pqxx::work tr{ conn };
    tr.exec("INSERT INTO Clients(first_name, last_name, email)"
        "VALUES('" + tr.esc(name) + "', '" + tr.esc(famil) + "', '" + tr.esc(mail) + "'); ");

    int id = tr.query_value<int>("SELECT id FROM Clients"\
                                    "WHERE first_name ='" + tr.esc(name)
                                    + "' AND last_name = '" + tr.esc(famil)
                                    + "' AND mail = '" + tr.esc(mail)
                                    +"' ORDER BY id DESC LIMIT 1;");

    tr.commit();
    return id;
}

void DBclass::addPhone(int id, std::string number) {
    pqxx::work tr{ conn };
    int count = tr.query_value<int>("SELECT COUNT(*) FROM Clients WHERE id =" + tr.esc(id) + ";");
    if (count == 0)
        throw std::exception("нет такого клиента");

    tr.exec("INSERT INTO phoneNumber(client_id, number)"
        "VALUES('" + tr.esc(id) + "', '" + tr.esc(number) + "'); ");
    tr.commit();
}

std::vector<DBinfoClient> DBclass::get(std::string name, std::string fam, std::string mail, std::string num) {
    pqxx::work tr{ conn };
    std::string condition;
    bool haveCond = false;
    if (!name.empty() || !fam.empty() || !mail.empty() || !num.empty()) {
        condition += "WHERE ";
        haveCond = true;
    }
    else
        throw std::exception("Некорректный запрос get");

    if (!name.empty()) {
        condition += "first_name = '" + name + "' AND ";
    }
    if (!fam.empty()) {
        condition += "last_name = '" + fam + "' AND ";
    }
    if (!mail.empty()) {
        condition += "email = '" + mail + "' AND ";
    }
    if (!num.empty()) {
        condition += "number = '" + num + "' AND ";
    }
    if (haveCond)
        condition.resize(condition.size() - 6);

    std::vector<DBinfoClient> result;
    for (auto [first_name, last_name, email, number, id] : 
        tr.query<std::string, std::string, std::string, std::string, int>(
            "SELECT first_name, last_name, email, number, id FROM Clients"
            "LEFT JOIN phoneNumber pN ON Clients.id = pN.client_id"
            + tr.esc(condition) + " ORDER BY id );")
        )
    {
        DBinfoClient tmp{ id, first_name, last_name, email, number };
        result.push_back(tmp);
    }

    return result;
}


void DBclass::updateClient(int id, std::string name, std::string fam, std::string mail) {
    pqxx::work tr{ conn };
    std::string condition;
    if (name.empty() && fam.empty() && mail.empty()) {
        return;
    }
    if (!name.empty()) {
        condition += "first_name = '" + name + ", ";
    }
    if (!fam.empty()) {
        condition += "last_name = '" + fam + ", ";
    }
    if (!mail.empty()) {
        condition += "email = '" + mail + "', ";
    }
    condition.resize(condition.size() - 2);

    tr.exec("UPDATE Clients SET " + tr.esc(condition) + " WHERE id=" + tr.esc(id) + " ;");
    tr.commit();
}

void DBclass::deleteClient(int id) {
    pqxx::work tr{ conn };
    tr.exec("DELETE FROM Clients WHERE id = " + tr.esc(id) + ";");
    tr.exec("DELETE FROM phoneNumber WHERE client_id = " + tr.esc(id) + ";");
    tr.commit();
}

void DBclass::deletePhone(std::string num) {
    pqxx::work tr{ conn };
    tr.exec("DELETE FROM phoneNumber WHERE number = " + tr.esc(num) + ";");
    tr.commit();
}


