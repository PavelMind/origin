#pragma once
#include <vector>
#include <deque>
#include <string>


class Orgraph {
	std::vector<std::vector<bool> > arr;
	int N;
	
	void alloc(int);
	void topologyRoundRecurs(int, std::deque<int>&, std::vector<bool>&);
public:
	Orgraph();
	~Orgraph();
	int getN() { return N; }

	void fRead(std::string);
	void print();
	void topologyRound();	
};