#pragma once
#include "track.h"

class airTrack : public track {
public:
	airTrack();
	 void registration(baseTransport* tr) override;
	
};