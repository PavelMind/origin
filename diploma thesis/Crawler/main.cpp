#include <iostream>
#include "DBManager.h"
#include "data base/sql_query_builders.h"
#include "indexator/indexator.h"
#include "threads pool/threads_pool_arg.h"
#include <boost/locale.hpp>
#include "ini-parser/parser.h"
#include "iterateSite.h"
#include <exception>
#include "http_connect.h"



int fooRet() { throw 2; return 666; }

int fooII(int a, int b) { return a + b; }

std::string strFoo(std::string s) {
    return "begin " + s;
}

int main() {
    setlocale(LC_ALL, "Russian");
    setlocale(LC_NUMERIC, "C");    
    
    //thread_pool_a pool(5);
    try{        
        /*std::string site{ "-end" };
        auto res2 = pool.submit(strFoo, site);
        auto res3 = pool.submit(fooII, 3, 7);
        auto s = res2.get();
        auto i = res3.get();
        std::cout << s<<" "<<i;*/        
    }
    catch (int d) { std::cout << "throw: " << d; }
    
    indexator ind;//call to boost::locale
    std::wstring str{ L"<tags> 343 ‘Ù”Ûƒ‰" };
    ind.indexation(str);


    return 0;
}