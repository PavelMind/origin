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
    badUp() : badCommand(L"Ошибка! отсутствует родитель."){}
};

class badLeft : public badCommand {
public:
    badLeft() : badCommand(L"Ошибка! отсутствует левый потомок.") {}
};

class badRight : public badCommand {
public:
    badRight() : badCommand(L"Ошибка! отсутствует правый потомок.") {}
};

class badInput : public badCommand {
public:
    badInput() : badCommand(L"Некорректный ввод.") {}
};

enum result {
    ok,
    bad,
    Exit
};