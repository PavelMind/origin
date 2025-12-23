#include "big_integer.h"

big_integer::big_integer() {
    arrNumber.push_back(0);
}

big_integer::big_integer(int number) {
    std::vector<char> tempVec;
    for (int i = 0; i < 10; ++i) {

        long long divider = 1;
        for (int j = 0; j < i; ++j) {
            divider *= 10;
        }

        long long digit;
        digit = number / divider;
        digit = digit % 10;
        tempVec.push_back(digit);
    }

    for (int i = tempVec.size() - 1; i >= 0; --i) {
        if (tempVec[i] == 0)
            tempVec.pop_back();
        else
            break;
    }
    arrNumber = std::move(tempVec);
}

big_integer::big_integer(long long number) {
    std::vector<char> tempVec;
    for (int i = 0; i < 19; ++i) { 
        
        long long divider = 1;
        for (int j = 0; j < i; ++j) {
            divider *= 10;
        }

        long long digit;
        digit = number / divider;        
        digit = digit % 10;
        tempVec.push_back(digit);
    }

     
    for (int i = tempVec.size() - 1; i >= 0; --i) {
        if (tempVec[i] == 0)
            tempVec.pop_back();
        else
            break;
    }
    arrNumber = std::move(tempVec);
}

big_integer::big_integer(std::string& str) {
    int length = str.length();
    if (length == 0) {
        arrNumber.push_back(0);
        return;
    }
    constexpr int dif= static_cast<int>('0');
    for (int i = str.length() - 1; i >= 0 ; --i) {        
        arrNumber.push_back(str[i]-dif);
    }
}

big_integer::big_integer(const char* str) {
    if (str[0] == '\0') {
        arrNumber.push_back(0);
        return;
    }
    int length = strlen(str);
    constexpr int dif = static_cast<int>('0');
    for (int i = length - 1; i >= 0; --i) {
        arrNumber.push_back(str[i] - dif);
    }
}

big_integer::~big_integer() = default;

big_integer::big_integer(const big_integer& other) {
    arrNumber = other.arrNumber;
}

big_integer::big_integer(const big_integer&& other) noexcept {
    arrNumber = std::move(other.arrNumber);
}

big_integer& big_integer::operator = (const big_integer& other) {
    arrNumber = other.arrNumber;
    return *this;
}

big_integer& big_integer::operator = (const big_integer&& other) noexcept {
    arrNumber = std::move(other.arrNumber);
    return *this;
}

big_integer operator + (const big_integer& a, const big_integer& b) {
    big_integer result;
    result.arrNumber.clear();
    int aSize = a.arrNumber.size();
    int bSize = b.arrNumber.size();
    int i = 0;
    int transferNum = 0;
    while ((i < aSize || i < bSize) || transferNum != 0) {
        int aCurrent = 0, bCurrent = 0;
        if (i < aSize) {
            aCurrent = a.arrNumber[i];
        }
        if (i < bSize) {
            bCurrent = b.arrNumber[i];
        }
        int tempSum = aCurrent + bCurrent + transferNum;

        transferNum = tempSum / 10;
        result.arrNumber.push_back(tempSum % 10);
        ++i;
    }
    return result;
}


big_integer big_integer::multyNum(int mult) const {
    big_integer result;
    if (mult != 0) {
        result=(*this );
    }
    else
        return result;

    int i = 0;
    int transferNum = 0;
    while (true) {
        int tempMult = arrNumber[i] * mult + transferNum;
        result.arrNumber[i] = tempMult % 10;        
        transferNum = tempMult / 10;
        ++i;
        if (i == arrNumber.size()) {
            if (transferNum != 0) {
                result.arrNumber.push_back(transferNum);
                break;
            }
            else
                break;
        }
    }
    return result;
}

big_integer operator * (const big_integer& a, const big_integer& b) {
    big_integer result;
    for (int i = 0; i < a.arrNumber.size(); ++i) {
        auto temp = b.multyNum(a.arrNumber[i]);

        if (i > 0) {
            int startSize = temp.arrNumber.size();
            temp.arrNumber.resize(startSize + i);
            for (int j = startSize - 1; j >= 0; --j) {
                temp.arrNumber[j + i] = temp.arrNumber[j];
            }
            for (int j = 0; j < i; ++j) {
                temp.arrNumber[j] = 0;
            }
        }
        result = result + temp;
    }
    return result;
}

std::ostream& operator <<(std::ostream& s, big_integer& num) {
    for (int i = num.arrNumber.size() - 1; i >= 0; --i) {
        s << static_cast<int>(num.arrNumber[i]);
    }
    return s;
}