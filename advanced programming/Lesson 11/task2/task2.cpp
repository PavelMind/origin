#include <iostream>
#include "big_integer.h"
#include <limits>

int main()
{
    std::string str{ "9990111222000111000" };
    big_integer big{ str };
    std::cout << "big : "<<big << "\n";

    big_integer big2{ std::numeric_limits<long long>::max() };
    std::cout << "big2: " << big2 << "\n";
    
    auto sum = big + big2;        
    std::cout << "sum: " << sum << "\n";

    big_integer big3 = { "22333000111000111000111" };
    std::cout << "big3: " << big3 << "\n";

    big_integer big4{ 1'000'000'000'000 };
    std::cout << "big4: " << big4 << "\n";

    auto mult = big3 *  big4;
    std::cout << "mult: " << mult << "\n";

    auto multNum = big3 * 10;
    std::cout << "mult(big3 * 10): " << multNum << "\n";

    big_integer big5{ "999999999999999999999" };
    auto moreBig = big5 + 1;
    std::cout << "more(+1): " << moreBig << "\n";

    auto number1 = big_integer("114575");
    auto number2 = big_integer("78524");
    auto result = number1 + number2;
    std::cout << result; // 193099
}
