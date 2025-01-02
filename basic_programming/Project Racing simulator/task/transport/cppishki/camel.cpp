#include "camel.h"


camel::camel() : groundTransport(L"Верблюд", transport::camel, 10, 30) {}
double camel::repose(int count){
	if (count == 1) return 5;
	return 8;
}