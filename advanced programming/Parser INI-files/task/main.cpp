#include <iostream>
#include <windows.h>
#include "myexpect.h"
#include "parser.h"



int main()
{
    //SetConsoleCP(1251);
    //SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
     
    try {
        ini_parser parser("file.ini");
        auto value = parser.get_value<int>("Section2.var1");
        std::cout << value;
    }
    catch (std::invalid_argument const& ex) {
        std::cout << "Некорректное значение переменной. Ошибка в: " << ex.what() ;
    }
    catch (std::exception& e) {
        std::cout << e.what();
    }
    catch (myexpect& mye) {
        std::wcerr << mye.what() << "\nСтрока файла номер: " << mye.numberErrLine();
    }
    
}
