#pragma once

#include <iostream>


class Counter {
    int count;
public:
    Counter();
    Counter(int co);
    void print();
    void increm();
    void decrem();

};