#include "allTrack.h"

allTrack::allTrack() : track(typeTrack::all) {}

void allTrack::registration(baseTransport* tr) {
	
	sharedRegistration(tr);

	arr[Count++] = tr;
}