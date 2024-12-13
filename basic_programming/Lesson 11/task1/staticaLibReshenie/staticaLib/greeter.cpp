#include "greeter.h"

std::wstring spaceGr::Greeter::greet(std::wstring str) {
	return L"Здравствуйте, " + str;
}