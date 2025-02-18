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

///////task2
void smart_array::operator=(smart_array& other) {
	if (reservSZ < other.currentSZ)
		alloc(other.currentSZ);
	currentSZ = other.currentSZ;

	for(int i = 0; i < currentSZ; ++i) {
		arr[i] = other.arr[i];
	}

}




void smart_array::alloc(int sz) {
	reservSZ = sz;
	int* temp = new int[reservSZ];
	
	currentSZ = reservSZ < currentSZ ? reservSZ : currentSZ;
	
	for (int i = 0; i < currentSZ; ++i) {
		temp[i] = arr[i];
	}
	delete[] arr;
	arr = temp;

}

void smart_array::add_element(int elem) {
	if (currentSZ >=  reservSZ)
		alloc(currentSZ * 2);
	arr[currentSZ++] = elem;
}

int smart_array::get_element(int index) {
	if (index >= 0 && index < currentSZ)
		return arr[index];
	else
		throw std::exception("bad range");
}