#include "boots.h"


boots::boots() : groundTransport(L"�������-���������", transport::boots, 6, 60) {}
double boots::repose(int count) {
	if (count == 1) return 10;
	return 5;
}