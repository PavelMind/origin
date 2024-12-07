#include <iostream>

class Fraction
{
private:
	int numerator_;
	int denominator_;

public:
	Fraction(int numerator, int denominator)
	{
		numerator_ = numerator;
		denominator_ = denominator;
	}
	bool operator==(Fraction obj2) {
		if (numerator_ == obj2.numerator_ && denominator_ == obj2.denominator_) return true;
		return false;
	}
	bool operator !=(Fraction obj2) {
		return !(*this == obj2);
	}

	bool operator < (Fraction obj2) {
		if( (static_cast<double>(numerator_)/denominator_) < 
			(static_cast<double>(obj2.numerator_) / obj2.denominator_) )
		{
			return true;
		}
		return false;
	}
	bool operator > (Fraction obj2) {
		if ((static_cast<double>(numerator_) / denominator_) >
			(static_cast<double>(obj2.numerator_) / obj2.denominator_))
		{
			return true;
		}
		return false;
	}

	bool operator <=(Fraction obj2) {
		return !(*this > obj2);
	}
	bool operator >=(Fraction obj2) {
		return !(*this < obj2);
	}
};

int main()
{
	Fraction f1(4, 3);
	Fraction f2(6, 11);

	std::cout << "f1" << ((f1 == f2) ? " == " : " not == ") << "f2" << '\n';
	std::cout << "f1" << ((f1 != f2) ? " != " : " not != ") << "f2" << '\n';
	std::cout << "f1" << ((f1 < f2) ? " < " : " not < ") << "f2" << '\n';
	std::cout << "f1" << ((f1 > f2) ? " > " : " not > ") << "f2" << '\n';
	std::cout << "f1" << ((f1 <= f2) ? " <= " : " not <= ") << "f2" << '\n';
	std::cout << "f1" << ((f1 >= f2) ? " >= " : " not >= ") << "f2" << '\n';
	return 0;
}