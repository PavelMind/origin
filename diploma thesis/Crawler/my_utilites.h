#pragma once
#include <string>
#include <vector>

using multString = std::wstring;

std::string convertWStrToStr(const multString&);

multString convertUTF8(const std::string&);