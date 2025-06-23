#pragma once
#include <string>

enum class Type {
    warning,
    error,
    fatalError,
    unknown
};

class LogMessage {
    Type _type;
    std::string _message;
public:
    LogMessage(Type tp, std::string mssg):_type(tp), _message(mssg){}
    Type type() const {
        return _type;
    }
    const std::string& message() const {
        return _message;
    }
};