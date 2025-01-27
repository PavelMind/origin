#pragma once
#include <string>


class badCommand {
    std::wstring str;
public:
    badCommand(std::wstring strr) : str(strr) {}
    virtual std::wstring what() { return str; }
};

class badUp : public badCommand {
public:
    badUp() : badCommand(L"������! ����������� ��������."){}
};

class badLeft : public badCommand {
public:
    badLeft() : badCommand(L"������! ����������� ����� �������.") {}
};

class badRight : public badCommand {
public:
    badRight() : badCommand(L"������! ����������� ������ �������.") {}
};

class badInput : public badCommand {
public:
    badInput() : badCommand(L"������������ ����.") {}
};

enum result {
    ok,
    bad,
    Exit
};