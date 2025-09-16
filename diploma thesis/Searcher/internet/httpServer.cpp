#include "httpServer.h"
#include <fstream>
#include <exception>
#include <chrono>
#include <boost/locale.hpp>
#include "../data base/sql_query_builders.h"


HTTPserver::HTTPserver(std::string host, int port, std::shared_ptr<DBclass> db)
#ifdef S_CPPHTTPLIB_OPENSSL_SUPPORT_S
    : serv( cert, key )
#endif 
{
    DB = db;
    readMyStartHtml();
    if (errServer) {
        serv.Get("/", [&](const httplib_S::Request& req, httplib_S::Response& res) {
            res.set_content("<html>\n<body><p>ERROR ON SERVER</p></body>\n</html>", "text/html");
            }
        );
    }
    else{
        serv.Get("/", [&](const httplib_S::Request& req, httplib_S::Response& res) {
            res.set_content(mainHTML, "text/html");
            }
        );

        serv.Post("/", [&](const httplib_S::Request& req, httplib_S::Response& res) {
            std::string stringReq = req.form.get_field("nameLabl");
            std::string newPage = "/" + stringReq;
            serv.Get(newPage, [=](const httplib_S::Request&, httplib_S::Response& res) {
                res.set_content(createListResp(stringReq), "text/html");
                });

            res.set_redirect(newPage);
            }
        );
    }
    
    
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
#ifdef CPPHTTPLIB_OPENSSL_SUPPORT_S
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
    if (errServer) {
        serv.Get("/", [&](const httplib_S::Request& req, httplib_S::Response& res) {
            res.set_content("<html>\n<body><p>ERROR ON SERVER</p></body>\n</html>", "text/html");
            }
        );
    }
    else {
        serv.Get("/", [&](const httplib_S::Request& req, httplib_S::Response& res) {
            res.set_content(mainHTML, "text/html");
            }
        );

        serv.Post("/", [&](const httplib_S::Request& req, httplib_S::Response& res) {
            std::string stringReq = req.form.get_field("nameLabl");
            std::string newPage = "/" + stringReq;
            serv.Get(newPage, [=](const httplib_S::Request&, httplib_S::Response& res) {
                res.set_content(createListResp(stringReq), "text/html");
                });

            res.set_redirect(newPage);
            }
        );
    }


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
        std::cout<<"Not open file \"main_crawler.html\"";
        errServer = true;
        return;
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    mainHTML = std::move(buffer.str());
    file.close();
}

std::string HTTPserver::createListResp(std::string stringReq) {
    boost::locale::generator gen;
    std::locale utf8Loc(gen(""));
    stringReq = boost::locale::to_lower(stringReq, utf8Loc);

    for (auto i : stringReq) {
        if (i == '\'')
            i = ' ';
    }

    std::string text{ "<html>\n<head>\n<title>Result</title>\n" };
    text += "<style>p{margin-top: 1px;margin-bottom: 0.1px;}h5{margin-top: 0.1px;margin-bottom: 1px;}</style>";
    text += "</head>\n<body>\n" ;
    text += "<table align=\"left\" border=\"1\" cellpadding=\"1\" cellspacing=\"1\" id=\"id_table_req\" style=\"width: 500px\">";
    text += "\n<tbody ><tr><td>" + stringReq + "</td></tr></tbody></table><p>&nbsp; </p><p>&nbsp; </p>\n";

    std::vector<std::string> words;
    createListWords(words, stringReq);
    auto siteList = reqFromDB(words);

    if (errServer) {
        return std::string{ "<html>\n<body><p>ERROR ON SERVER</p></body>\n</html>" };
    }
    for (auto& i : siteList) {
        text += "\n<p>" + i.first + "</p>" + "\n<h5> <a href = \"" +
            i.second + "\" id = \"id\" name = \"name\" target = \"_blank\" title = \"handle\" type = \"type\">" + i.second + "</a>\n</h5>" +
            "<p>&nbsp; </p>";
    }
    if (siteList.empty())
        text += "\n<p>nothing found</p>";
    text += "</body>\n</html> ";
    return text;
}

void HTTPserver::createListWords(std::vector<std::string>& words, const std::string& strReq) {
    const char* badChar = { " ,./\\|\"\'\t\n\r\f\b\v!@#$%^?¹&*(){}[]=+;:~`" };
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
        

        SqlSelectQueryBuilder sqlReq;
        sqlReq.AddColumn("title").AddColumn("URL").AddColumn("SUM(count_word) AS su").AddFrom("counts").
            AddJoin(JoinType::INNER, "counts", "id_word", "words", "id").
            AddJoin(JoinType::INNER, "counts", "id_site", "sites", "id").
            AddGroupBy("title").AddGroupBy("URL").AddOrderByDesc("su").AddLimit("10");
        for (auto& i : words) {
            sqlReq.AddWhereOr("word", i);
        }

        for (auto [ti, url, c] : tr.query<std::string, std::string, int>(sqlReq.BuildQuery()))
        {
            result.push_back({ ti, url });
        }
    }
    catch (pqxx::sql_error erPQXX) { 
        errServer = true;
        std::cout << erPQXX.what() << std::endl; 
    }
    catch (std::exception e) { 
        errServer = true;
        std::cout << e.what() << std::endl; 
    }

    return result;
}
