#include <iostream>
#include <windows.h>
#include "myexpect.h"
#include "parser.h"
#include "paparser.h"


int main()
{
    //SetConsoleCP(1251);
    //SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
    std::setlocale(LC_NUMERIC, "C"); // ���� std::stod  �� ������� ����� ����� '.'
    //  int
    //  double
    //  std::string

    try {
        var2::ini_parser parser("file.ini");        
        auto value = parser.get_value<double>("Section1.var1");
        std::cout <<std::fixed<< value;        

    }
    catch (std::invalid_argument const& ex) {
        std::cout << "������������ �������� ����������. ������ �: " << ex.what() ;
    }
    catch (std::exception& e) {
        std::cout << e.what();
    }
    catch (myexpect& mye) {
        std::wcout << mye.what() ;
        std::cout << "\n������ ����� �����: " << mye.numberErrLine();
    }
    
}
