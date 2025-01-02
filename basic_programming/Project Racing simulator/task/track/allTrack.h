#pragma once
#include "track.h"

class allTrack : public track {
public:
	allTrack();
	void registration(baseTransport* tr) override;

};