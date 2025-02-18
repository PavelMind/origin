#include "smart_array.h"
#include <exception>

smart_array::smart_array(int SZ): currentSZ(0), reservSZ(SZ) {
	if (SZ <= 0) {
		throw std::exception("bad size");
	}
	arr = new int[SZ];
}

smart_array::~smart_array() {
	delete[] arr;
}

void smart_array::alloc() {
	reservSZ = currentSZ * 2;
	int* temp = new int[reservSZ];
	for (int i = 0; i < currentSZ; ++i) {
		temp[i] = arr[i];
	}
	delete[] arr;
	arr = temp;

}

void smart_array::add_element(int elem) {
	if (currentSZ >=  reservSZ)
		alloc();
	arr[currentSZ++] = elem;
}

int smart_array::get_element(int index) {
	if (index >= 0 && index < currentSZ)
		return arr[index];
	else
		throw std::exception("bad range");
}