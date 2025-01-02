#include "airTransport.h"

airTransport::airTransport(std::wstring n, transport typ, int spd) : baseTransport(n, true, typ), speed(spd) {}

double airTransport::rasing(int distance) { 
	double tempDist = distance * (100 - koef(distance)) / 100.0;
	return tempDist / speed;
}