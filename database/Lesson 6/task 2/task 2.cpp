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
            "dbname=test "
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

        //insert:

        Wt::Dbo::Transaction transaction{ session };
        std::unique_ptr<publisher> pisar{ new publisher() };
        pisar->name = "Писарчук";
        Wt::Dbo::ptr<publisher> pisarPtr = session.add(std::move(pisar));
        transaction.commit();

        
        std::unique_ptr<book> eleph{ new book() };
        eleph->title = "Трудно быть слоном"; 
        eleph->pPublisher = pisarPtr;
        Wt::Dbo::ptr<book> elephPtr = session.add(std::move(eleph));
        transaction.commit();

        
        std::unique_ptr<book> jung{ new book() };
        jung->title = "Джунгли на Марсе";
        jung->pPublisher = pisarPtr;
        Wt::Dbo::ptr<book> jungPtr = session.add(std::move(jung));
        transaction.commit();

        
        std::unique_ptr<shop> zaread{ new shop() };
        zaread->name = "Зачитаешься";
        Wt::Dbo::ptr<shop> zareadPtr = session.add(std::move(zaread));
        transaction.commit();

        std::unique_ptr<shop> paper{ new shop() };
        paper->name = "Бумага в чернилах";
        Wt::Dbo::ptr<shop> paperPtr = session.add(std::move(paper));
        transaction.commit();
        
        std::unique_ptr<stock> stocker{ new stock() };
        stocker->count = 50;
        stocker->pBook = jungPtr;
        stocker->pShop = zareadPtr;
        Wt::Dbo::ptr<stock> stockPtr = session.add(std::move(stocker));
        transaction.commit();
        
        std::unique_ptr<stock> stocker2{ new stock() };
        stocker2->count = 20;
        stocker2->pBook = jungPtr;
        stocker2->pShop = paperPtr;
        stockPtr = session.add(std::move(stocker2));
        transaction.commit();

        
        std::unique_ptr<sale> blackSale{ new sale() };
        blackSale->count = 10;
        blackSale->price = 100500;
        blackSale->data_sale = "попробуй не купи";
        blackSale->pStock = stockPtr;
        Wt::Dbo::ptr<sale> blackPtr = session.add(std::move(blackSale));
        transaction.commit();

        //select:

                
        int id;
        std::cin >> id;
        Wt::Dbo::ptr<publisher> publ = session.find<publisher>().where("id = ?").bind(id);
        std::cout << publ->name << std::endl;

        for (auto Fbook : publ->books) {
            for (auto Fstock : Fbook->stocks) {
                auto Fshop = Fstock->pShop;
                std::cout << Fshop->name << std::endl;
            }
        }

        
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
