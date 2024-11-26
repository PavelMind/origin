#include "counter.h"

Counter::Counter() : count(1) { }

Counter::Counter(int co) : count(co) { }

void Counter::print() { std::cout << count << std::endl; }

void Counter::increm() {
    count++;
}

void Counter::decrem() {
    count--;
}
