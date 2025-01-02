#pragma once
#include "baseTransport.h"

class airTransport: public baseTransport {
	int speed;
public:
	airTransport(std::wstring n, transport typ, int spd);
	virtual int koef(int) = 0;
	virtual double rasing(int distance); //возвращает время до конца дистанции
		
};