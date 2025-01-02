#include "broom.h"


broom::broom() : airTransport(L"Метла", transport::broom, 20) {}
int broom::koef(int distance) { 
	int k = distance / 1000;
	return k;
}