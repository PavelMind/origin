#include "groundTrack.h"

groundTrack::groundTrack() : track(typeTrack::ground) {}

void groundTrack::registration(baseTransport* tr) {
	if (tr->isAir()) {
		throw errorReg(L"Ќеправильный тип регистрируемого транспорта!");
	}
	sharedRegistration(tr);

	arr[Count++] = tr;
}