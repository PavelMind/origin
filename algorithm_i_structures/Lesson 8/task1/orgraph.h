#pragma once
#include <vector>
#include <string>


class Orgraph {
	std::vector<std::vector<bool> > arr;
	int N;

	void alloc(int);
public:
	Orgraph();
	~Orgraph();
	void fRead(std::string);
	void print();	
};