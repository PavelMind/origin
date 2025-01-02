#pragma once
#include "track.h"

class groundTrack : public track {
public:
	groundTrack();
	void registration(baseTransport* tr) override;
	
};