#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <math.h>

class big_integer {    
    std::vector<char> arrNumber;

    big_integer multyNum(int);
public:
    big_integer();
    big_integer(long long);
    big_integer(const char*);
    big_integer(std::string&);
    ~big_integer();

    big_integer(big_integer&);
    big_integer(big_integer&&);
    big_integer& operator = (big_integer&);
    big_integer& operator = (big_integer&&);

    friend big_integer operator + (big_integer& const, big_integer& const);
    friend big_integer operator * (big_integer& const, big_integer& const);

    friend std::ostream& operator <<(std::ostream&, big_integer&);//?????????????
};