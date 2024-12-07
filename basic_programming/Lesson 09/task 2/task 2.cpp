#include <iostream>


class Fraction
{
private:
	int numerator_;
	int denominator_;

public:
	Fraction(): numerator_(0), denominator_(0){}
	Fraction(int numerator, int denominator)
	{
		numerator_ = numerator;
		denominator_ = denominator;
	}
	
	void setNumerator(int m) { numerator_ = m; }
	void setDenominator(int m) { denominator_ = m; }

	//определенны ниже
	friend void downFraction(Fraction&);
	friend void commonMult(Fraction& , Fraction& );

	bool operator==(Fraction obj2) {
		if (numerator_ == obj2.numerator_ && denominator_ == obj2.denominator_) return true;
		return false;
	}
	bool operator !=(Fraction obj2) {
		return !(*this == obj2);
	}

	bool operator < (Fraction obj2) {
		if ((static_cast<double>(numerator_) / denominator_) <
			(static_cast<double>(obj2.numerator_) / obj2.denominator_))
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

	Fraction operator +(Fraction obj2) {
		Fraction A=*this;
		commonMult(A, obj2);
		A.numerator_ += obj2.numerator_;
		downFraction(A);
		return A;
	}

	Fraction operator -(Fraction obj2) {
		Fraction A = *this;
		commonMult(A, obj2);
		A.numerator_ -= obj2.numerator_;
		downFraction(A);
		return A;
	}

	Fraction operator *(Fraction& obj2) {
		Fraction out;
		out.numerator_ = numerator_ * obj2.numerator_;
		out.denominator_ = denominator_ * obj2.denominator_;
		downFraction(out);
		return out;
	}

	Fraction operator /(Fraction& obj2) {
		Fraction out;
		out.numerator_ = numerator_ * obj2.denominator_;
		out.denominator_ = denominator_ * obj2.numerator_;
		downFraction(out);
		return out;
	}

	Fraction& operator ++() {
		numerator_ += denominator_;
		return *this;
	}
	Fraction operator ++(int) {
		Fraction out=*this;
		this->numerator_ += denominator_;
		return out;
	}

	Fraction& operator --() {
		numerator_ -= denominator_; 
		return *this;
	}

	Fraction operator --(int) {
		Fraction out = *this;
		this->numerator_ -= denominator_;
		return out;
	}
	
	friend std::ostream& operator <<(std::ostream& , Fraction& );
};

std::ostream& operator <<(std::ostream& s, Fraction& f){
	s << f.numerator_ << "/" << f.denominator_;
	return s;
}

void inline commonMult(Fraction& a, Fraction& b) {
	int temp = a.denominator_;
	a.denominator_ *= b.denominator_;
	a.numerator_ *= b.denominator_;

	b.denominator_ *= temp;
	b.numerator_ *= temp;
	
}

void downFraction(Fraction& a) {
	int min = a.numerator_ > a.denominator_ ? a.denominator_ : a.numerator_;

	for (int i = min; i >= 2; --i) {
		int t1, t2;

		t1 = a.numerator_ % i;
		t2 = a.denominator_ % i;
		if (t1 == 0 && t2 == 0) {
			a.numerator_ /= i;
			a.denominator_ /= i;
		}
	}
}



int main()
{
	setlocale(LC_ALL, "Russian");
	Fraction f1;
	Fraction f2;
	int temp;

	std::cout << "Введите числитель дроби 1: ";
	std::cin >> temp;
	f1.setNumerator(temp);
	std::cout << "Введите знаменатель дроби 1: ";
	std::cin >> temp;
	f1.setDenominator(temp);

	std::cout << "Введите числитель дроби 2: ";
	std::cin >> temp;
	f2.setNumerator(temp);
	std::cout << "Введите знаменатель дроби 2: ";
	std::cin >> temp;
	f2.setDenominator(temp);
	
	
	Fraction F = f1 + f2;
	std::cout << f1 << " + " << f2 << " = " << F << std::endl;

	F = f1 - f2;
	std::cout << f1 << " - " << f2 << " = " << F << std::endl;

	F = f1 * f2;
	std::cout << f1 << " * " << f2 << " = " << F << std::endl;

	F = f1 / f2;
	std::cout << f1 << " / " << f2 << " = " << F << std::endl;

	std::cout << "++" << f1 << " * " << f2 << " = ";
	F = ++f1 * f2;
	std::cout<< F << std::endl;
	std::cout << "Значение дроби 1 = " << f1 << std::endl;

	std::cout << f1 << "-- * " << f2 << " = " ;
	F = f1-- * f2;
	std::cout << F << std::endl;
	std::cout << "Значение дроби 1 = " << f1<< std::endl;

	return 0;
}