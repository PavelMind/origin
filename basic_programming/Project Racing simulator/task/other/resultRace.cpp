#include "resultRace.h"

resultRace::resultRace(unsigned int c) : ccount(c) {
	arr = new pairResult[ccount];
}
resultRace::~resultRace() {
	delete[] arr; 
}

pairResult& resultRace::operator[](int i) {
	return arr[i];
}

resultRace::resultRace(resultRace& other) {
	int max = other.ccount;
	this->ccount = max;
	arr = new pairResult[max];
	for (int i = 0; i < max; ++i) {

		this->arr[i] = other.arr[i];
	}
}

	void resultRace::sort() { //по возростанию от [0]->[max]
		for (int i = 0; i < ccount-1; ++i) {
			for (int j = i + 1; j < ccount; ++j) {
				if (arr[i].time > arr[j].time)
				{
					pairResult temp = arr[j];
					arr[j] = arr[i];
					arr[i] = temp;
				}
			}
		}

	}
