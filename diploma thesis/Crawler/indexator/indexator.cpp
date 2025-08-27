#include "indexator.h"
#include <iostream>
#include <boost/locale.hpp>
#include <algorithm>

indexator::indexator(std::shared_ptr<DBclass> b): DB(b) {
    readBlackList();
}

std::vector<addrSite>&& indexator::getLinks() {
    return std::move(links); 
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
                    
                    addrSite st(strAddr, currS.SSL(), currS.host());
                    bool noInBlack = std::find(blackListSite.begin(), blackListSite.end(), st.host()) == blackListSite.end();
                    bool noInList = std::find(links.begin(), links.end(), st) == links.end();
                    if (st.ref() && noInList && noInBlack) {
                        links.push_back(st);
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
    links.clear();
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
    int i;
    auto smolTitle = title.substr(0, 29);
    std::vector<int> resSite;
    try {
        pqxx::work db{ DB->getConn() };
        std::string url = site.url();
        if (url.size() > 50)
            return;
        for (auto [i] : db.query<int>("SELECT id FROM sites WHERE URL = '" + db.esc(url) + "';"))
        {
            resSite.push_back(i);
        }
        if (resSite.empty()) {
            db.exec("INSERT INTO sites(title, URL) VALUES('" + db.esc(smolTitle) + "', '" + db.esc(url) + "');");
            db.commit();
            for (auto [i] : db.query<int>("SELECT id FROM sites WHERE URL = '" + db.esc(url) + "';"))
            {
                resSite.push_back(i);
            }
        }        
    }
    catch (pqxx::sql_error& erPQXX) { std::cout << "Err pqxx to site" << std::endl << erPQXX.what(); }
    catch (std::exception& e) { std::cout << "Err to site" << std::endl << e.what(); }

    std::string forErr;
    for (auto word : words) {
        if (word.size() > 20)
            continue;
        try {
            pqxx::work db{ DB->getConn() };
            forErr = word;
            std::vector<int> resWord;
            for (auto [i] : db.query<int>("SELECT id FROM words WHERE word = '" + db.esc(word) + "';"))
            {
                resWord.push_back(i);
            }
            if (resWord.empty()) {
                db.exec("INSERT INTO words(word) VALUES('" + db.esc(word) + "');");
                for (auto [i] : db.query<int>("SELECT id FROM words WHERE word = '" + db.esc(word) + "';"))
                {
                    resWord.push_back(i);
                }
            }
            if (resWord.empty() || resSite.empty())
                continue;
            std::vector<int> resCount;
            for (auto [i] : db.query<int>("SELECT count_word FROM counts WHERE"
                " id_word = " + std::to_string(resWord[0]) + " AND id_site = " + std::to_string(resSite[0]) + ";"))
            {
                resCount.push_back(i);
            }
            if (resCount.empty()) {
                db.exec("INSERT INTO counts(id_site, id_word, count_word)"
                    " VALUES(" + std::to_string(resSite[0]) + ", " + std::to_string(resWord[0]) + ", " + std::to_string(1) + ");");
            }
            else {
                db.exec("UPDATE counts SET count_word = " + std::to_string((resCount[0]) + 1) +
                    " WHERE id_site = " + std::to_string(resSite[0]) + " AND id_word = " + std::to_string(resWord[0]) + ";");
            }
            db.commit();
        }
        catch (pqxx::sql_error& erPQXX) { std::cout << "Err pqxx to word" << forErr << std::endl << erPQXX.what(); }
        catch (std::exception& e) { std::cout << "Err to word" << forErr << std::endl << e.what(); }

    }
}

