#pragma once
// NOT USED
#include <string>

using multString = std::wstring;

std::string convertW_to_Str(const multString&);

multString convertStr_to_W(const std::string&);

std::u16string convertStr_to_16s(const std::string&);

std::string convert16s_to_Str(const std::u16string&);
std::wstring convertStr_to_W_2(const std::string& str);