#include "indexator.h"
#include <iostream>
#include <boost/locale.hpp>
//#include "../data base/sql_query_builders.h"

indexator::indexator(std::shared_ptr<DBclass> b): DB(b) {}

std::vector<std::string>&& indexator::getLinks() { return std::move(links); }



void indexator::cleanerText(std::string& text, std::string& title){
    boost::locale::generator gen;
    std::locale utf8Loc(gen(""));
    text = boost::locale::to_lower(text, utf8Loc);
    
    size_t sizeText = text.size();
    bool isProcessed = false;
    bool takedTitle = false;

    for (size_t i = 0; i < sizeText; ++i) {
        if (text[i] == '<') {
            size_t endDeleted=0;

            if (!takedTitle && text.substr(i + 1, 6) == "title>") {
                int endTitl = text.find("</title>", i + 7);
                if(endTitl==-1)
                    throw errorOfTextSite{};
                title = text.substr(i + 7, endTitl - i - 7);
                takedTitle = true;
            }

            if (text.substr(i + 1, 8) == "a href=\"") {
                size_t beginAddr = i + 9;
                size_t endAddr = text.find("\"", beginAddr + 1);
                if (endAddr != std::string::npos)
                    --endAddr;
                else
                    throw errorOfTextSite{};
                std::string Waddr = text.substr(beginAddr, endAddr - beginAddr + 1);                
                links.push_back(Waddr);
            }

            for (auto& j : rangeTags) {
                if (text.substr(i + 1, j.size() ) == j && 
                    i + j.size() < sizeText - 1 && 
                    text[i + j.size() + 1] == '>') 
                {
                    size_t posBeginClose = text.find("</" + j + ">", i + j.size());
                    if (posBeginClose != std::string::npos)
                        endDeleted = posBeginClose + j.size() + 2;
                    else
                        throw errorOfTextSite{};
                    isProcessed = true;
                    continue;
                }
            }
            if (!isProcessed) {
                endDeleted = text.find(">", i + 1);
                if (endDeleted == std::string::npos)
                    throw errorOfTextSite{};
            }            
            isProcessed = false;

            while (i != endDeleted){
                text[i] = ' ';
                ++i;
            }
            text[endDeleted] = ' ';
        }

        if (delitedChar.find(text[i]) != std::string::npos) {
            text[i] = ' ';            
        }

    }//for
}



void indexator::indexation(std::string& text, const std::string& site) {
    std::string title{};
    cleanerText(text, title);
    std::string word;

    size_t size = text.size();
    size_t beginWord = 0;
    size_t endWord = 0;
    size_t i = 0;
    bool run = true;

    while (run){
        beginWord = text.find_first_not_of(" ", i);
        if (beginWord == std::string::npos) {
            break;
        }
        i = text.find(" ", beginWord);
        if (i != std::string::npos) {
            endWord = i - 1;
        }
        else {
            endWord = size - 1;
            run = false;
        }

        size_t lengthWord = (endWord - beginWord) + 1;
        if (lengthWord < minSizeWord || lengthWord > maxSizeWord)
            continue;
        word = text.substr(beginWord, lengthWord);
        inputBD(site, title, word);
    }
}

void indexator::inputBD(const std::string& site, const std::string& title, const std::string& word) {
    
    try {
        pqxx::work db{ DB->getConn() };

        int i;
        std::vector<int> resSite;

        for (auto [i] : db.query<int>("SELECT id FROM sites WHERE URL = '" + db.esc(site) + "';"))
        {
            resSite.push_back(i);
        }
        if (resSite.empty()) {
            db.exec("INSERT INTO site(title, URL) VALUES('" + db.esc(title) + "', '" + db.esc(site) + "');");
            db.commit();
        }

        std::vector<int> resWord;
        for (auto [i] : db.query<int>("SELECT id FROM words WHERE word = '" + db.esc(word) + "';"))
        {
            resWord.push_back(i);
        }
        if (resWord.empty()) {
            db.exec("INSERT INTO words(word) VALUES('" + db.esc(word) + "');");
            db.commit();
        }

        std::vector<int> resCount;
        for (auto [i] : db.query<int>("SELECT count_word FROM counts WHERE"
            " id_word = " + std::to_string(resWord[0]) + " AND id_site = " + std::to_string(resSite[0]) + ";"))
        {
            resCount.push_back(i);
        }
        if (resCount.empty()) {
            db.exec("INSERT INTO counts(id_site, id_word, count_word)"
                " VALUES(" + std::to_string(resSite[0]) + ", " + std::to_string(resWord[0]) + ", " + std::to_string(0) + ");");
            db.commit();
        }
        else {
            db.exec("UPDATE counts SET count_word = " + std::to_string((resCount[0]) + 1) +
                " WHERE id_site = " + std::to_string(resSite[0]) + " AND id_word = " + std::to_string(resWord[0]) + ";");
            db.commit();
        }
    }
    catch (pqxx::sql_error erPQXX) { std::cout << "Err to word" << word <<std::endl<< erPQXX.what(); }
    catch (std::exception e) { std::cout << "Err to word" << word << std::endl << e.what(); }
}

