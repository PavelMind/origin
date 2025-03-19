#include <iostream>
#include <windows.h>
#include "myexpect.h"
#include "parser.h"



int main()
{
    //SetConsoleCP(1251);
    //SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
    std::setlocale(LC_NUMERIC, "C"); // чтоб std::stod  не удаляла цифры после '.'
    //  int
    //  double
    //  std::string

    try {
        ini_parser parser("file.ini");
        auto value = parser.get_value<double>("Section1.var1");
        std::cout <<std::fixed<< value;

    }
    catch (std::invalid_argument const& ex) {
        std::cout << "Некорректное значение переменной. Ошибка в: " << ex.what() ;
    }
    catch (std::exception& e) {
        std::cout << e.what();
    }
    catch (myexpect& mye) {
        std::wcout << mye.what() ;
        std::cout << "\nСтрока файла номер: " << mye.numberErrLine();
    }
    
}
