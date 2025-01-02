#include "track.h"
#include "../other/resultRace.h"

track::track(typeTrack tp) : Distance(0), Count(0), Type(tp) {}
track::~track() {
	for (int i = 0; i < count(); ++i) {
		delete arr[i];
	}
}

void track::setDist(int d) { Distance = d; }
std::wstring track::list(){
	int cnt = count();	
	std::wstring str{};
	if (cnt == 0) str = L"\nТранспортных средств не зарегистрировано.";
	else str = L"\nЗарегестрированны в гонке: ";
	bool first = true;
	for (int i = 0; i < cnt; ++i) {
		if (first) { 
		str = str + arr[i]->name(); 
		first = false; 
		}
		else str = str + L", " + arr[i]->name();
	}
	return str;
}

resultRace track::race(){
	unsigned int maxTS = count();
	unsigned int distan = distance();
	resultRace result(maxTS);
	for (int i = 0; i < maxTS; ++i) {
		result[i].name = arr[i]->name();
		result[i].time = arr[i]->rasing(distance() );
	}
	return result;
}

void track::sharedRegistration(baseTransport* tr) {
	for (int i = 0; i < Count; i++) {
		if (arr[i]->transportType() == tr->transportType()) {
			throw errorReg(tr->name() + L" уже был зарегистрирован! Транспорт повторяться не должен.");
		}
	}
}