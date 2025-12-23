#include "commands.h"


int main()
{
    LogCommand* logFile = new fileLogCommand;
    LogCommand* logConsol = new consolLogCommand;
    print(logFile, "str in file");
    print(logConsol, "str in consol");
    delete logFile;
    delete logConsol;
}
