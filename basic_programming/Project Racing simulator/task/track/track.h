#pragma once
#include "baseTransport.h"
#include "../other/resultRace.h"
#include <string>

enum class typeTrack {
	all, ground, air
};

class track {
protected:
	unsigned int Distance;
	baseTransport* arr[10];
	unsigned int Count;
	typeTrack Type;

	void sharedRegistration(baseTransport* );
public:
	track(typeTrack);
	~track();
	virtual void registration(baseTransport*) =0;
	unsigned int distance() { return Distance; };
	unsigned int count() { return Count; }
	typeTrack type() { return Type; }

	void setDist(int);
	std::wstring list();

	resultRace race();
};

class errorReg {
	std::wstring message;
public:
	errorReg(std::wstring n): message(n){}
	std::wstring what() { return message; }
};