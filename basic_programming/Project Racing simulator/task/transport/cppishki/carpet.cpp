#include "carpet.h"


carpet::carpet() : airTransport(L"Ковёр-самолёт", transport::carpet, 10) {}
int carpet::koef(int distance) { 
	if (distance < 1000) return 0;
	else if (distance < 5000) return 3;
	else if (distance < 10000) return 10;
	else return 5;

}