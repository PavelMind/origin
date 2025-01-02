#include "airTrack.h"

airTrack::airTrack() : track(typeTrack::air) {}

void airTrack::registration(baseTransport* tr) {
	if (!tr->isAir()) {
		 throw errorReg(L"������������ ��� ��������������� ����������!");
	}
	sharedRegistration(tr);

	arr[Count++] = tr;
}