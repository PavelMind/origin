#pragma once


class smart_array {
	int* arr;
	size_t currentSZ;
	size_t reservSZ;

	void alloc();
public:
	smart_array(int);
	~smart_array();
	void add_element(int);
	int get_element(int);

};

