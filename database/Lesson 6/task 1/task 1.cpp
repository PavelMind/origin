#include <iostream>
#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/Postgres.h>
#include <exception>
#include "classes.h"


int main()
{
    setlocale(LC_ALL, "Russian");
    try
    {
        std::string connectionString =
            "host=localhost "
            "port=5432 "
            "dbname=my_database "
            "user=postgres "
            "password=2222 ";
        
        auto postgres = std::make_unique<Wt::Dbo::backend::Postgres>(connectionString);
        Wt::Dbo::Session session;
        session.setConnection(std::move(postgres));
        session.mapClass<publisher>("publisher");
        session.mapClass<book>("book");
        session.mapClass<stock>("stock");
        session.mapClass<sale>("sale");
        session.mapClass<shop>("shop");

        session.createTables();
    }
    catch (const Wt::Dbo::Exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    catch (const std::exception& stdexc)
    {
        std::cout << stdexc.what() << std::endl;
    }
}
