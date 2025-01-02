#include "groungTransport.h"

groundTransport::groundTransport(std::wstring n, transport typ, int spd, int time) :
	baseTransport(n, false, typ), speed(spd), powerTime(time) {	}

double groundTransport::rasing(int distance) { 
	double timeInRun = (double)distance / speed;
	int maxCountWait = timeInRun / powerTime;
	for (int countWait = 1; countWait <= maxCountWait; ++countWait) {
		timeInRun += repose(countWait);
	}
	return timeInRun;
}