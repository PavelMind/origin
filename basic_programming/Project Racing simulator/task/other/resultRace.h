#pragma once
#include "baseTransport.h"
#include <string>

struct pairResult{
	std::wstring name;
	double time;
};

class resultRace {
	pairResult* arr;
	unsigned int ccount;
public:
	resultRace(unsigned int c);
	~resultRace();
	pairResult& operator[](int i);
	
	resultRace(resultRace& other);
	unsigned int count() { return ccount; }

	void sort();
};