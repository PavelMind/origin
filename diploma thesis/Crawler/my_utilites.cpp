#include "my_utilites.h"

std::string convertWStrToStr(const multString& wstr) {
    size_t required_size = wcstombs(nullptr, wstr.c_str(), 0);
    std::vector<char> buffer(required_size + 1);
    size_t converted_len = wcstombs(buffer.data(), wstr.c_str(), required_size + 1);
    std::string str(buffer.data());
    return str;
}


multString convertUTF8(const std::string& s) {
    return std::wstring{ L"convrtUTF8util" };
}