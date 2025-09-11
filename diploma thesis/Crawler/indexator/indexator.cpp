#include "indexator.h"
#include <iostream>
#include <boost/locale.hpp>
#include <algorithm>
#include "../data base/sql_query_builders.h"

const std::string indexator::delitedChar{ ",./\\|\"\'\t\n\r\f\a\b\v!@#$%^?¹&*(){}[]-_=+;:~`" };
const std::vector<std::string> indexator::rangeTags{ "style", "script", "code", "button" };

indexator::indexator(std::shared_ptr<DBclass> b, std::shared_ptr<listLinks> l): DB(b), prLinks(l) {
    readBlackList();
}

void indexator::getAdded(int& site, int& word, int& upd) {
    site = addedS;
    word = addedW;
    upd = updatedW;
}

void indexator::readBlackList() {
    std::ifstream file("black_list_site.txt");
    if (!file.is_open()) {
        throw std::exception("Not open file \"black_list_site.txt\"");
    }
    while (file) {
        std::string str;
        file >> str;
        blackListSite.push_back(str);
    }
    file.close();
}

void indexator::cleanerText(std::string& text, std::string& title, const addrSite& currS){
    boost::locale::generator gen;
    std::locale utf8Loc(gen(""));
    text = boost::locale::to_lower(text, utf8Loc);
    
    size_t sizeText = text.size();
    bool isProcessed = false;
    bool takedTitle = false;
    for (size_t i = 0; i < sizeText; ++i) {
        if (text[i] == '<') {
            size_t endDeleted = 0;

            if (!takedTitle && text.substr(i + 1, 6) == "title>") {
                int endTitl = text.find("</title>", i + 7);
                if (endTitl == -1)
                    throw errorOfTextSite{};
                title = text.substr(i + 7, endTitl - i - 7);
                takedTitle = true;
            }

            if (text.substr(i + 1, 2) == "a ") {
                int begH, endA, begSt, endSt, pClick;
                std::string strAddr;

                endA = text.find('>', i + 2);
                if (endA != -1) {
                    std::string tag = text.substr(i + 1, endA - i - 1);
                    begH = tag.find("href", 2);
                    if (begH != -1) {
                        begSt = tag.find("\"", begH + 4);
                        if (begSt != -1) {
                            endSt = tag.find("\"", begSt + 1);
                            pClick = tag.find(" onclick=", begSt + 1);
                            if (pClick == -1)
                                pClick = tag.find("\"onclick=", begSt + 1);
                            if (endSt != -1 && endSt - begSt > 1 && (pClick == -1 || pClick > endSt))
                                strAddr = tag.substr(begSt + 1, endSt - begSt - 1);
                        }
                    }
                }
                else
                    throw errorOfTextSite{};
                if (strAddr.size() > 0) {                    
                    addrSite st(strAddr, currS);
                    bool noInBlack;                    
                    {
                        std::lock_guard<std::mutex> mut{ mtxBlack };
                        noInBlack = std::find(blackListSite.begin(), blackListSite.end(), st.host()) == blackListSite.end();
                    }
                    if (st.ref() && noInBlack) {
                        prLinks->push(st);
                    }
                }
            }// if(... == "a ")
            
            for (auto& j : rangeTags) {
                if (text.substr(i + 1, j.size() ) == j) 
                {
                    size_t posEndOpen = text.find(">", i + j.size());
                    size_t posBeginClose = text.find("</" + j + ">", posEndOpen);
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
        } //if (text[i] == '<')

        if (text[i] == '&') {
            size_t endDeleted = 0;
            size_t pos;
            if (text[i + 1] == '#'){                
                pos = text.find(';', i + 2);
                if (pos != -1 && pos - i <= 6) {
                    endDeleted = pos;
                }
            }
                        
            if (text.substr(i, 6) == "&nbsp;") {
                endDeleted = i + 5;
            }
            if (endDeleted != 0) {
                while (i != endDeleted) {
                    text[i] = ' ';
                    ++i;
                }
                text[endDeleted] = ' ';
            }
        }

        if (delitedChar.find(text[i]) != std::string::npos) {
            text[i] = ' ';            
        }

    }//for
}


void indexator::indexation(std::string& text, const addrSite& currSite) {
    std::string title{};
    cleanerText(text, title, currSite);
    std::vector<std::string> words;

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
        std::string word = text.substr(beginWord, lengthWord);
        words.push_back(word);
    }
    inputBD(currSite, title, words);
}

void indexator::inputBD(const addrSite& site, const std::string& title, const std::vector<std::string>& words) {
    if (words.empty())
        return;    
    auto smolTitle = title.substr(0, DB->lengthTitle()-1);
    for (auto i : smolTitle) {
        if (i == '\'')
            i = ' ';
    }

    int i;
    std::vector<int> resSite;

    std::lock_guard<std::mutex> mutx{ mtxDB };
    try {
        pqxx::work db{ DB->getConn() };
        std::string url = site.url();        
        if (url.size() > DB->lengthUrl()) {
            std::string underSizeStr{ "Site length exceeded: " + site.url() + "\n" };
            std::cout << underSizeStr;
            return;
        }

        SqlSelectQueryBuilder sqlSelSite;
        sqlSelSite.AddColumn("id").AddFrom("sites").AddWhereAnd("URL", url);
        for (auto [i] : db.query<int>(sqlSelSite.BuildQuery()))
        {
            resSite.push_back(i);
        }
        if (resSite.empty()) {
            SqlInsertQueryBuilder sqlInsSite;
            sqlInsSite.AddNameTable("sites").AddColumn("title", smolTitle).AddColumn("URL", url);
            db.exec(sqlInsSite.BuildQuery());
            ++addedS;
            for (auto [i] : db.query<int>(sqlSelSite.BuildQuery()))
            {
                resSite.push_back(i);
            }
        }
        db.commit();
    }
    catch (pqxx::sql_error& erPQXX) { 
        std::cout << "Err DB pqxx to site. " << erPQXX.what() << std::endl; 
        return;
    }
    catch (std::exception& e) { 
        std::cout << "Err DB to site. "  << e.what() << std::endl; 
        return;
    }

    std::string forErr;
    const int maxLengthWord = DB->lengthWord();
    for (auto word : words) {
        if (word.size() > maxLengthWord) {
            std::string underSizeStr{ "Word length exceeded: " + word + "\n" };
            std::cout << underSizeStr;
            continue;
        }
        try {
            pqxx::work db{ DB->getConn() };
            forErr = word;
            std::vector<int> resWord;
            SqlSelectQueryBuilder sqlSelWord;
            sqlSelWord.AddColumn("id").AddFrom("words").AddWhereAnd("word", word);
            for (auto [i] : db.query<int>(sqlSelWord.BuildQuery()))
            {
                resWord.push_back(i);
            }
            if (resWord.empty()) {
                SqlInsertQueryBuilder sqlInsWord;
                sqlInsWord.AddNameTable("words").AddColumn("word", word);
                db.exec(sqlInsWord.BuildQuery());
                ++addedW;
                for (auto [i] : db.query<int>(sqlSelWord.BuildQuery()))
                {
                    resWord.push_back(i);
                }
            }
            if (resWord.empty() || resSite.empty())
                continue;
            std::vector<int> resCount;

            SqlSelectQueryBuilder sqlSelCW;
            sqlSelCW.AddFrom("counts").AddColumn("count_word").AddWhereAnd("id_word", resWord[0]).AddWhereAnd("id_site", resSite[0]);
            for (auto [i] : db.query<int>(sqlSelCW.BuildQuery()))
            {
                resCount.push_back(i);
            }
            
            if (resCount.empty()) {
                SqlInsertQueryBuilder sqlInsCW;
                sqlInsCW.AddNameTable("counts").AddColumn("id_site", resSite[0]).AddColumn("id_word", resWord[0]).AddColumn("count_word", 1);
                db.exec(sqlInsCW.BuildQuery());
            }
            else {
                SqlUpdateQueryBuilder sqlUpdCW;
                sqlUpdCW.AddNameTable("counts").AddColumnValue("count_word", resCount[0] + 1).
                    AddWhereAnd("id_site", resSite[0]).AddWhereAnd("id_word", resWord[0]);
                db.exec(sqlUpdCW.BuildQuery());
                ++updatedW;
            }
            db.commit();           
        }
        catch (pqxx::sql_error& erPQXX) { 
            std::cout << "Err DB pqxx to word " << forErr << std::endl << erPQXX.what() << std::endl; 
            continue;
        }
        catch (std::exception& e) { 
            std::cout << "Err DB to word " << forErr << std::endl << e.what() << std::endl; 
            continue;
        }
    }//for
}

