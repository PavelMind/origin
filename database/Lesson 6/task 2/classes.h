#pragma once
#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/Postgres.h>
#include <string>


class book;
class stock;
class shop;
class sale;

class publisher {
public:
    std::string name = "";
    Wt::Dbo::collection< Wt::Dbo::ptr<book> > books;

    template<typename Action>
    void persist(Action& a) {
        Wt::Dbo::field(a, name, "name");
        Wt::Dbo::hasMany(a, books, Wt::Dbo::ManyToOne, "publisher");
    }
};

class book {
public:
    std::string title = "";
    Wt::Dbo::ptr<publisher> pPublisher;
    Wt::Dbo::collection< Wt::Dbo::ptr<stock> > stocks;

    template<class Action>
    void persist(Action& a)
    {
        Wt::Dbo::field(a, title, "title");
        Wt::Dbo::belongsTo(a, pPublisher, "id_publisher");
        Wt::Dbo::hasMany(a, stocks, Wt::Dbo::ManyToOne, "book");
    }
};

class stock {
public:
    int count = 0;
    Wt::Dbo::ptr<book> pBook;
    Wt::Dbo::ptr<shop> pShop;
    Wt::Dbo::collection < Wt::Dbo::ptr<sale> > sales;

    template<class Action>
    void persist(Action& a)
    {
        Wt::Dbo::field(a, count, "count");
        Wt::Dbo::belongsTo(a, pBook, "id_book");
        Wt::Dbo::belongsTo(a, pShop, "id_shop");
        Wt::Dbo::hasMany(a, sales, Wt::Dbo::ManyToOne, "stock");
    }
};


class sale {
public:
    int price = 0;
    std::string data_sale;
    int count = 0;
    Wt::Dbo::ptr<stock> pStock;

    template<class Action>
    void persist(Action& a)
    {
        Wt::Dbo::field(a, price, "price");
        Wt::Dbo::field(a, data_sale, "data_sale");
        Wt::Dbo::field(a, count, "count");
        Wt::Dbo::belongsTo(a, pStock, "id_stock");
    }
};

class shop {
public:
    std::string name = "";
    Wt::Dbo::collection< Wt::Dbo::ptr<stock> > stocks;

    template<class Action>
    void persist(Action& a)
    {
        Wt::Dbo::field(a, name, "name");
        Wt::Dbo::hasMany(a, stocks, Wt::Dbo::ManyToOne, "shop");
    }
};

