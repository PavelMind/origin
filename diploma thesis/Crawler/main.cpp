#include <iostream>
#include "DBManager.h"
#include "data base/sql_query_builders.h"
#include "indexator/indexator.h"
#include "threads pool/threads_pool.h"
#include <boost/locale.hpp>
#include "ini-parser/parser.h"



int main() {
    setlocale(LC_ALL, "Russian");
    setlocale(LC_NUMERIC, "C");
    
    
    //auto const host = "duskworld.ru";
    //auto const port = "80";
    //auto const target = "/";
    //int version = 11;

    //net::io_context ioc;

    //std::promise<std::string> promise;
    //std::future<std::string> future = promise.get_future();

    //std::make_shared<session>(ioc, promise)->run(host, port, target, version);

    //ioc.run();

    //// Получаем результат из future
    //std::string result = future.get();
    //std::cout << "Ответ сервера: " << result << std::endl;
    ////if (c.connect("duskworld.ru", "80", "/", 11) == EXIT_FAILURE)std::cout << "bad";
    try {
        std::string nameF{ "crawler_data.ini" };
        ini_parser ini(nameF);
        std::string host = ini.get_value<std::string>("DB.host");
        std::string port = ini.get_value<std::string>("DB.port");
        std::string DBname = ini.get_value<std::string>("DB.name");
        std::string user = ini.get_value<std::string>("DB.user");
        std::string password = ini.get_value<std::string>("DB.password");
        std::cout << host << " " << port << " " << DBname << " " << user << " " << password;
    }
    catch (myexpect& m) { std::wcout << m.what(); }
    catch (std::exception& e) { std::cout << e.what(); }
    return 0;
}