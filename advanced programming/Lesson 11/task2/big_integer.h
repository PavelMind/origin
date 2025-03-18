#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <math.h>

class big_integer {    
    std::vector<char> arrNumber;

    big_integer multyNum(int)const ;
public:
    big_integer();
    big_integer(int);
    big_integer(long long);
    big_integer(const char*);
    big_integer(std::string&);
    ~big_integer();

    big_integer(const big_integer&);
    big_integer(const big_integer&&) noexcept;
    big_integer& operator = (const big_integer&);
    big_integer& operator = (const big_integer&&) noexcept;

    friend big_integer operator + (const big_integer&, const big_integer&);
    friend big_integer operator * (const big_integer&, const big_integer&);

    friend std::ostream& operator <<(std::ostream&, big_integer&);
};