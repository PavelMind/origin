#pragma once
#include "baseTransport.h"

class groundTransport : public baseTransport {
	int speed;
	int powerTime;
public:
	groundTransport(std::wstring n, transport typ, int spd, int time);
	
	virtual double repose(int) = 0;
	virtual double rasing(int distance); //возвращает время до конца дистанции
		
};