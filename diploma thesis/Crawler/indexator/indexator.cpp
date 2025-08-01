#include "indexator.h"
#include <iostream>
#include <boost/locale.hpp>


std::vector<std::string>&& indexator::getLinks() { return std::move(links); }

//void indexator::cleanLinks() { links.clear(); }

void indexator::cleanerText(multString& text){
    boost::locale::generator gen;
    std::locale utf8Loc(gen(""));
    text = boost::locale::to_lower(text, utf8Loc);
    
    size_t sizeText = text.size();
    bool isProcessed = false;

    for (size_t i = 0; i < sizeText; ++i) {
        if (text[i] == '<') {
            size_t endDeleted=0;

            if (text.substr(i + 1, 8) == L"a href=\"") {
                size_t beginAddr = i + 9;
                size_t endAddr = text.find(L"\"", beginAddr + 1);
                if (endAddr != std::string::npos)
                    --endAddr;
                else
                    throw errorOfTextSite{};
                multString Waddr = text.substr(beginAddr, endAddr - beginAddr + 1);
                std::string addr = convertWStrToStr(Waddr);
                links.push_back(addr);
            }

            for (auto& j : rangeTags) {
                if (text.substr(i + 1, j.size() ) == j && 
                    i + j.size() < sizeText - 1 && 
                    text[i + j.size() + 1] == '>') 
                {
                    size_t posBeginClose = text.find(L"</" + j + L">", i + j.size());
                    if (posBeginClose != std::string::npos)
                        endDeleted = posBeginClose + j.size() + 2;
                    else
                        throw errorOfTextSite{};
                    isProcessed = true;
                    continue;
                }
            }
            if (!isProcessed) {
                endDeleted = text.find(L">", i + 1);
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
            ++i;
        }

    }//for
}



void indexator::indexation(multString& text) {
    cleanerText(text);
    multString word;

    size_t size = text.size();
    size_t beginWord = 0;
    size_t endWord = 0;
    size_t i = 0;
    bool run = true;

    while (run){
        beginWord = text.find_first_not_of(L" ", i);
        if (beginWord == std::string::npos) {
            break;
        }
        i = text.find(L" ", beginWord);
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
        inputBD(word);
    }
}
void print(multString s) {
    std::wcout <<L"\nÁÄ<-:"<< s << "|\n";
    // -incude
}
void indexator::inputBD(const multString& word) {
    print(word);
}

