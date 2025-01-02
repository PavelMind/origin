#include "centaur.h"


centaur::centaur() : groundTransport(L"Кентавр", transport::centaur, 15, 8) {}
double centaur::repose(int count) { return 2; }