#include <iostream>

class Calculator {
    double num1, num2;
public:
    double add() {
        return num1 + num2;
    }
    double multiply() {
        return num1 * num2;
    }
    double subtract_1_2() {
        return num1 - num2;
    }
    double subtract_2_1() {
        return num2 - num1;
    }

    double divide_1_2() {
        return num1 / num2;
    }

    double divide_2_1() {
        return num2 / num1;
    }

    bool set_num1(double num1) {
        if (num1 != 0) {
            this->num1 = num1;
            return true;
        }
        return false;
    }
    bool set_num2(double num2) {
        if (num2 != 0) {
            this->num2 = num2;
            return true;
        }
        return false;
    }

};

/*
bool(Calculator::* setNum)(double);

void seter (Calculator obj, bool(Calculator::*setNum)(double) ){
    while (true) {
        double n;
        std::cout << "Введите num1: ";
        std::cin >> n;
        if ((obj.*setNum)(n))
            break;
        else {
            std::cout << "Неверный ввод!" << std::endl;
            continue;
        }
    }
};*/

void  main()
{
    setlocale(LC_ALL, "Russian");
    Calculator calc;
    while (true) {
        while (true) {
            double n1;
            std::cout << "Введите num1: ";
            std::cin >> n1;
            if (calc.set_num1(n1))
                break;
            else {
                std::cout << "Неверный ввод!" << std::endl;
                continue;
            }
        } //while num1
        while (true) {
            double n2;
            std::cout << "Введите num2: ";
            std::cin >> n2;
            if (calc.set_num2(n2))
                break;
            else {
                std::cout << "Неверный ввод!" << std::endl;
                continue;
            }
        } //while num2

        /* setNum = &Calculator::set_num1;
        seter(calc, setNum);
        setNum = &Calculator::set_num2;
        seter(calc, setNum); */

        std::cout << std::endl;
        std::cout << "num1 + num2 = " << calc.add()<<std::endl;
        std::cout << "num1 - num2 = " << calc.subtract_1_2() << std::endl;
        std::cout << "num2 - num1 = " << calc.subtract_2_1() << std::endl;
        std::cout << "num1 * num2 = " << calc.multiply() << std::endl;
        std::cout << "num1 / num2 = " << calc.divide_1_2() << std::endl;
        std::cout << "num2 / num1 = " << calc.divide_2_1() << std::endl << std::endl;
    }

    
}

