#include "camelFast.h"


camelFast::camelFast() : groundTransport(L"Верблюд-быстроход", transport::camelFast, 40, 10) {}
double camelFast::repose(int count) {
	if (count == 1) return 5;
	if (count == 2) return 6.5;
	return 8;
}