#include "airTrack.h"

airTrack::airTrack() : track(typeTrack::air) {}

void airTrack::registration(baseTransport* tr) {
	if (!tr->isAir()) {
		 throw errorReg(L"Неправильный тип регистрируемого транспорта!");
	}
	sharedRegistration(tr);

	arr[Count++] = tr;
}