#include <iostream>
#include "handler.h"

int main()
{
    LogMessage mssg1(Type::warning, "Hello message"),
        mssg2(Type::error, "Bad message"),
        mssg3(Type::unknown, "Suspicious message"),
        mssg4(Type::fatalError, "Very bad message!");

    std::unique_ptr<handler> hendlWarn = std::make_unique<handlerWarning>();
    std::unique_ptr<handler> hendlErr = std::make_unique <handlerError>("log.txt");
    std::unique_ptr<handler> hendlFatErr = std::make_unique <handlerFatalError>();
    std::unique_ptr<handler> hendlUnkn = std::make_unique <handlerUnknown>();

    hendlFatErr->setNextHandler(std::move(hendlErr));
    hendlFatErr->setNextHandler(std::move(hendlWarn));
    hendlFatErr->setNextHandler(std::move(hendlUnkn));
    try {
        hendlFatErr->processing(mssg1);//warning
        //hendlFatErr->processing(mssg3);//unknown
        //hendlFatErr->processing(mssg2);//error
        //hendlFatErr->processing(mssg4);//fatalError
    }
    catch (programmMustDead& exc) {
        std::cout << std::endl << exc.what();
        return 1;
    }
    catch (std::exception& exc) {
        std::cout << std::endl << exc.what();
    }

    std::cout << "\nthe end";
    return 0;
}
