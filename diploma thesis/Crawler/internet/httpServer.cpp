#include "httpServer.h"
#include <fstream>
#include <exception>
#include <chrono>
//#include "../my_utilites.h"



HTTPserver::HTTPserver(std::string host, int port, std::shared_ptr<DBclass> db)
#ifdef CPPHTTPLIB_OPENSSL_SUPPORT
    : serv( cert, key ) 
#endif 
{
    DB = db;
    readMyStartHtml();
    serv.Get("/", [&](const httplib::Request& req, httplib::Response& res) {
        res.set_content(mainHTML, "text/html");
        }
    );

    serv.Post("/", [&](const httplib::Request& req, httplib::Response& res) {
        std::string stringReq = req.form.get_field("nameLabl");
        std::string newPage = "/" + stringReq;
        std::cout << newPage << " ";
        serv.Get(newPage, [=](const httplib::Request&, httplib::Response& res) {
            res.set_content(createListResp(stringReq), "text/html");
            });

        res.set_redirect(newPage);
        }
    );
    
    
    thrd = std::thread([&]() {
        serv.listen(host, port);
        });

    int tim = 0;
    using namespace std::literals::chrono_literals;
    while (!serv.is_running()) {        
        std::this_thread::sleep_for(1s);
        ++tim;
        if (tim > 6)
            throw std::exception("Time out of start HTTP server");
    }
}

HTTPserver::HTTPserver(ini_parser& p, std::shared_ptr<DBclass> db) 
#ifdef CPPHTTPLIB_OPENSSL_SUPPORT
    : serv(cert, key)
#endif 
{
    int port = 8080;
    try {
        port = p.get_value<int>("spider.port");
    }
    catch (myexpect& mye) {
        std::wcout << mye.what();
        std::cout << "In line:" << mye.numberErrLine();
    }
    catch (std::exception& e) {
        std::cout << e.what();
    }
    DB = db;
    readMyStartHtml();
    serv.Get("/", [&](const httplib::Request& req, httplib::Response& res) {
        res.set_content(mainHTML, "text/html");
        }
    );

    serv.Post("/", [&](const httplib::Request& req, httplib::Response& res) {
        std::string stringReq = req.form.get_field("nameLabl");
        std::string newPage = "/" + stringReq;
        std::cout << newPage << " ";
        serv.Get(newPage, [=](const httplib::Request&, httplib::Response& res) {
            res.set_content(createListResp(stringReq), "text/html");
            });

        res.set_redirect(newPage);
        }
    );


    thrd = std::thread([&]() {
        serv.listen("localhost", port);
        });

    int tim = 0;
    using namespace std::literals::chrono_literals;
    while (!serv.is_running()) {
        std::this_thread::sleep_for(1s);
        ++tim;
        if (tim > 6)
            throw std::exception("Time out of start HTTP server");
    }
}



HTTPserver::~HTTPserver() {
    if (serv.is_running())
        stop();
    thrd.join();
}

void HTTPserver::stop() {
    serv.stop();
}

void HTTPserver::readMyStartHtml() {
    std::ifstream file("main_crawler.html");
    if (!file.is_open()) {
        throw std::exception("Not open file \"main_crawler.html\"");
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    mainHTML = std::move(buffer.str());
    file.close();
}

std::string HTTPserver::createListResp(const std::string stringReq) {
    std::string text{ "<html>\n<head>\n<title>Результаты поиска</title>\n" };
    text += "<style>p{margin-top: 1px;margin-bottom: 0.1px;}h5{margin-top: 0.1px;margin-bottom: 1px;}</style>";
    text += "</head>\n<body>\n" ;
    text += "<table align=\"left\" border=\"1\" cellpadding=\"1\" cellspacing=\"1\" id=\"id_table_req\" style=\"width: 500px\">";
    text += "\n<tbody ><tr><td>" + stringReq + "</td></tr></tbody></table><p>&nbsp; </p><p>&nbsp; </p>\n";

    std::vector<std::string> words;
    createListWords(words, stringReq);
    auto siteList = reqFromDB(words);
    for (auto& i : siteList) {
        text += "\n<p>" + i.first + "</p>" + "\n<h5> <a href = \"" +
            i.second + "\" id = \"id\" name = \"name\" target = \"_blank\" title = \"handle\" type = \"type\">" + i.second + "</a>\n</h5>" +
            "<p>&nbsp; </p>";
    }

    text += "</body>\n</html> ";
    //std::cout << text;
    return text;
}

void HTTPserver::createListWords(std::vector<std::string>& words, const std::string& strReq) {
    const char* badChar = { " ,./\\|\"\'\t\n\r\f\b\v!@#$%^?№&*(){}[]=+;:~`" };
    int pBeg = 0;
    while (true) {
        pBeg = strReq.find_first_not_of(badChar, pBeg);
        if (pBeg != -1) {
            int pEnd = strReq.find_first_of(badChar, pBeg);
            if (pEnd != -1) {
                words.push_back(strReq.substr(pBeg, pEnd - pBeg));
                pBeg = pEnd;
                continue;
            }
            else
            {
                words.push_back(strReq.substr(pBeg));
                break;
            }
        }
        else
            break;
    }
}

std::vector<std::pair<std::string, std::string>> HTTPserver::reqFromDB(const std::vector<std::string>& words) {
    std::vector<std::pair<std::string, std::string>> result;
    
    try{
        pqxx::work tr{ DB->getConn() };
        std::string url, ti;
        int c;
        

        std::string req{ "SELECT title, URL, SUM(count_words) AS su FROM counter"
          " INNER JOIN words ON words.id = counter.id_word"
          " INNER JOIN sites ON sites.id = counter.id_site"
          " WHERE" };
        for (auto& w : words) {
            req += " word = \'" + tr.esc(w) + "\' OR";
        }
        req.resize(req.size() - 2);
        req += " GROUP BY title, URL"
            " ORDER BY su DESC"
            " LIMIT 10;";

        for (auto [ti, url, c] : tr.query<std::string, std::string, int>(req))
        {
            result.push_back({ ti, url });
        }
    }
    catch (pqxx::sql_error erPQXX) { std::cout << erPQXX.what(); }
    catch (std::exception e) { std::cout << e.what(); }

    /*SqlSelectQueryBuilder sqlReq;
    sqlReq.AddColumn("title").AddColumn("UR").AddColumn("SUM(count_words) AS su").AddFrom("counter").
        AddJoin(JoinType::INNER, "counter", "id_word", "words", "id").
        AddJoin(JoinType::INNER, "counter", "id_site", "sites", "id").
        AddGroupBy("title").AddGroupBy("UR").AddOrderByDesc("su").AddLimit("10");
    for (auto& i : words) {
        sqlReq.AddWhereOr("word", i);
    }*/
    

    /*struct strucSelect {
        std::string tit;
        std::string url;
        int summ;
    };
    std::string tmp1{};
    std::string tmp2{};
    int tmp3=0;*/
    //...
    //auto resultSelect = DB->selectMult<strucSelect>(req, tmp1, tmp2, tmp3);
    
    /*std::vector<std::pair<std::string, std::string>> result;
    std::string req = sqlReq.BuildQuery();
    auto resultSelect = DB->selectSiteList(req);
    for (auto& i : resultSelect) {
        result.push_back(std::pair(i.name, i.URL));
    }*/
    return result;
}
