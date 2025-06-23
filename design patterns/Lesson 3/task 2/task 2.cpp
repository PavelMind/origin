#include <iostream>
#include <string>
#include "observable.h"
//#include "observer.h"


int main()
{
    std::string nameFileLog{ "log.txt" };

    observable obsrvedString;
    Observer* obsW1 = new warningObserver;
    Observer* obsW2 = new warningObserver;
    Observer* obsW3 = new warningObserver;

    Observer* obsE1 = new errorObserver(nameFileLog);
    Observer* obsE2 = new errorObserver(nameFileLog);
    Observer* obsE3 = new errorObserver(nameFileLog);

    Observer* obsFE1 = new fatalErrorObserver(nameFileLog);
    Observer* obsFE2 = new fatalErrorObserver(nameFileLog);

    obsrvedString.addObserver(obsW1).addObserver(obsW2).addObserver(obsW3).
        addObserver(obsE1).addObserver(obsE2).addObserver(obsE3).
        addObserver(obsFE1).addObserver(obsFE2);

    obsrvedString.setString("Observ");
    obsrvedString.setString("Ob");
    obsrvedString.setString("");
    obsrvedString.setString("Observvvvvvvvvvv");
    obsrvedString.setString("Observ");

    delete obsW1;
    delete obsW2;
    delete obsW3;
    delete obsE1;
    delete obsE2;
    delete obsE3;
    delete obsFE1;
    delete obsFE2;
}
