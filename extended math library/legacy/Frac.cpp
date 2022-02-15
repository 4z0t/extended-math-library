#include "Frac.h"
int32_t gcd(const int32_t& value1, const int32_t& value2)
{
	int32_t n1 = abs(value1);
	int32_t n2 = abs(value2);
	while (n1 != n2)
	{
		if (n1 == 0)
			return n2;
		if (n2 == 0)
			return n1;
	
		if (n1 > n2)
			n1 %= n2;
		//n1 = n1 % n2;
		else
			n2 %= n1;
		//n2 = n2 % n1;

	}
	return n1;
}




Frac::Frac(const int32_t& numerator, const int32_t& denominator, bool check)
{
	if (denominator == 0)
		exit(ZERO_DIVISION_ERROR_CODE);
	if (numerator == 0)
	{
		this->numerator = 0;
		this->denominator = 1;
		return;
	}

	if (check)
	{
		int32_t gc = gcd(numerator, denominator);
		this->numerator = numerator / gc;
		this->denominator = denominator / gc;
	}
	else
	{
		this->numerator = numerator;
		this->denominator = denominator;
	}

	this->numerator *= (this->denominator > 0) ? 1 : -1;
	this->denominator = abs(this->denominator);
}

Frac::Frac(const int32_t& value)
{
	this->numerator = value;
	this->denominator = 1;
}



Frac::Frac()
{
	this->numerator = 0;
	this->denominator = 1;
}

Frac& Frac::operator=(const Frac& other)
{
	this->numerator = other.numerator;
	this->denominator = other.denominator;
	return *this;
}

bool Frac::operator==(const Frac& other)
{
	return this->numerator * other.denominator == this->denominator * other.numerator;
}

bool Frac::operator!=(const Frac& other)
{
	return this->numerator * other.denominator != this->denominator * other.numerator;
}

bool Frac::operator>(const Frac& other)
{
	return this->numerator * other.denominator > this->denominator * other.numerator;
}

bool Frac::operator>=(const Frac& other)
{
	return this->numerator * other.denominator >= this->denominator * other.numerator;
}

bool Frac::operator<(const Frac& other)
{
	return this->numerator * other.denominator < this->denominator* other.numerator;
}

bool Frac::operator<=(const Frac& other)
{
	return this->numerator * other.denominator <= this->denominator * other.numerator;
}

Frac Frac::operator*(const Frac& other)const
{
	return Frac(this->numerator * other.numerator, this->denominator * other.denominator);
}

Frac Frac::operator+(const Frac& other)const
{
	return Frac(this->numerator * other.denominator + this->denominator * other.numerator, this->denominator * other.denominator);
}

Frac Frac::operator-(const Frac& other)const
{
	return Frac(this->numerator * other.denominator - this->denominator * other.numerator, this->denominator * other.denominator);
}

Frac Frac::operator/(const Frac& other)const
{
	if (other.numerator == 0)
		exit(ZERO_DIVISION_ERROR_CODE);
	return Frac(this->numerator * other.denominator, this->denominator * other.numerator);
}


Frac Frac::operator-()const
{
	return Frac(-this->numerator, this->denominator, false);
}

Frac& Frac::operator+=(const Frac& other)
{
	this->numerator = this->numerator * other.denominator + this->denominator * other.numerator;
	this->denominator *= other.denominator;

	int32_t gc = gcd(this->numerator, this->denominator);
	this->numerator /= gc;
	this->denominator /= gc;
	return *this;
}

Frac& Frac::operator-=(const Frac& other)
{
	this->numerator = this->numerator * other.denominator - this->denominator * other.numerator;
	this->denominator *= other.denominator;
	int32_t gc = gcd(this->numerator, this->denominator);
	this->numerator /= gc;
	this->denominator /= gc;
	return *this;
}


Frac& Frac::operator*=(const Frac& other)
{
	this->numerator *= other.numerator;
	this->denominator *= other.denominator;
	int32_t gc = gcd(this->numerator, this->denominator);
	this->numerator /= gc;
	this->denominator /= gc;
	return *this;
}

Frac& Frac::operator/=(const Frac& other)
{
	if (other.numerator == 0)
		exit(ZERO_DIVISION_ERROR_CODE);
	this->numerator *= other.denominator;
	this->denominator *= other.numerator;
	int32_t gc = gcd(this->numerator, this->denominator);
	this->numerator /= gc;
	this->denominator /= gc;
	return *this;
}

//Frac Frac::operator%(const Frac& other)
//{
//	return Frac();
//}

/*

Frac& Frac::operator++()
{
	// TODO: вставьте здесь оператор return
}

Frac& Frac::operator++(int)
{
	// TODO: вставьте здесь оператор return
}

Frac& Frac::operator--()
{
	// TODO: вставьте здесь оператор return
}

Frac& Frac::operator--(int)
{
	// TODO: вставьте здесь оператор return
}
*/

Frac reciprocal(const int32_t& value)
{
	return Frac(1, value, false);
}

Frac reciprocal(const Frac& value)
{
	return Frac(value.denominator, value.numerator, false);
}

double Frac::operator~()const
{
	return double(this->numerator) / this->denominator;
}
//Frac pow(const Frac& value, const int& n)
//{
//	if (n > 0)
//		return Frac(pow(value.numerator, (uint32_t)n), pow(value.denominator, (uint32_t)n), false);
//	if (n < 0)
//	{
//		if (value.denominator==0)
//			exit(ZERO_DIVISION_ERROR_CODE);
//		else
//			return Frac(pow(value.denominator, (uint32_t)(-n)), pow(value.numerator, (uint32_t)(-n)), false);
//	}
//	return 1;
//}

