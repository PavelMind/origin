// NOT USED
#include "my_utilites.h"
#include <boost/locale.hpp>
#include <vector>
#include <locale>
#include <codecvt>
#include <iostream>

std::string convertW_to_Str(const multString& wstr) {
    size_t required_size = wcstombs(nullptr, wstr.c_str(), 0);
    std::vector<char> buffer(required_size + 1);
    size_t converted_len = wcstombs(buffer.data(), wstr.c_str(), required_size + 1);
    std::string str(buffer.data());
    return str;
}

multString convertStr_to_W(const std::string& s) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::string str = converter.to_bytes(L"Hello world");
    std::wstring wstr = converter.from_bytes(s);
    return wstr;
}

std::u16string convertStr_to_16s(const std::string& utf8_string) {
    return boost::locale::conv::utf_to_utf<char16_t>(utf8_string);
}

std::string convert16s_to_Str(const std::u16string& utf16_string) {
    return boost::locale::conv::utf_to_utf<char>(utf16_string);
}

std::wstring convertStr_to_W_2(const std::string& str) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    try {
        return converter.from_bytes(str);
    }
    catch (const std::range_error& e) {
        std::cout << "Conversion error: " << e.what() << std::endl;
        return L""; // or handle the error as needed
    }
}