#include "Fraction.h"

class Unreal;
Fraction::Fraction(const Unlint& numerator, const Unlint& denominator, bool check)
{
	//std::cout << denominator << std::endl;
	if (denominator.zero())
		exit(ZERO_DIVISION_ERROR_CODE);
	//std::cout << "test" << std::endl;
	if (numerator.zero())
	{
		this->numerator = 0;
		this->denominator = 1;
		return;
	}

	if (check)
	{
		Unlint gc = gcd(numerator, denominator);
		
		this->numerator = numerator / gc;
		this->denominator = denominator / gc;
	}
	else
	{
		this->numerator = numerator;
		this->denominator = denominator;
	}
	
	this->numerator.negative ^= this->denominator.negative;
	this->denominator.negative = false;
}

Fraction::Fraction(const Unlint& value)
{
	this->numerator = value;
	this->denominator = 1;
}



Fraction::Fraction(const int& value)
{
	this->numerator = value;
	this->denominator = 1;
}

Fraction::Fraction()
{
	this->numerator = 0;
	this->denominator = 1;
}

Fraction& Fraction::operator=(const Fraction& other)
{
	this->numerator = other.numerator;
	this->denominator = other.denominator;
	return *this;
}

bool Fraction::operator==(const Fraction& other)
{
	return this->numerator * other.denominator == this->denominator * other.numerator;
}

bool Fraction::operator!=(const Fraction& other)
{
	return this->numerator * other.denominator != this->denominator * other.numerator;
}

bool Fraction::operator>(const Fraction& other)
{
	return this->numerator * other.denominator > this->denominator * other.numerator;
}

bool Fraction::operator>=(const Fraction& other)
{
	return this->numerator * other.denominator >= this->denominator * other.numerator;
}

bool Fraction::operator<(const Fraction& other)
{
	return this->numerator * other.denominator < this->denominator* other.numerator;
}

bool Fraction::operator<=(const Fraction& other)
{
	return this->numerator * other.denominator <= this->denominator * other.numerator;
}

Fraction Fraction::operator*(const Fraction& other)const
{
	return Fraction(this->numerator * other.numerator, this->denominator * other.denominator);
}

Fraction Fraction::operator+(const Fraction& other)const
{
	return Fraction(this->numerator * other.denominator + this->denominator * other.numerator, this->denominator * other.denominator);
}

Fraction Fraction::operator-(const Fraction& other)const
{
	return Fraction(this->numerator * other.denominator - this->denominator * other.numerator, this->denominator * other.denominator);
}

Fraction Fraction::operator/(const Fraction& other)const
{
	
	if (other.numerator.zero())
		exit(ZERO_DIVISION_ERROR_CODE);
	
	return Fraction(this->numerator * other.denominator, this->denominator * other.numerator);
}


Fraction Fraction::operator-()const
{
	return Fraction(-this->numerator, this->denominator, false);
}

Fraction& Fraction::operator+=(const Fraction& other)
{
	this->numerator = this->numerator * other.denominator + this->denominator * other.numerator;
	this->denominator *= other.denominator;
	
	Unlint gc = gcd(this->numerator, this->denominator);
	
	this->numerator /= gc;
	this->denominator /= gc;
	return *this;
}

Fraction& Fraction::operator-=(const Fraction& other)
{
	this->numerator = this->numerator * other.denominator - this->denominator * other.numerator;
	this->denominator *= other.denominator;
	Unlint gc = gcd(this->numerator, this->denominator);
	this->numerator /= gc;
	this->denominator /= gc;
	return *this;
}


Fraction& Fraction::operator*=(const Fraction& other)
{
	this->numerator *= other.numerator;
	this->denominator *= other.denominator;
	Unlint gc = gcd(this->numerator, this->denominator);
	this->numerator /= gc;
	this->denominator /= gc;
	return *this;
}

Fraction& Fraction::operator/=(const Fraction& other)
{
	if (other.numerator.zero())
		exit(ZERO_DIVISION_ERROR_CODE);
	this->numerator *= other.denominator;
	this->denominator *= other.numerator;
	Unlint gc = gcd(this->numerator, this->denominator);
	this->numerator /= gc;
	this->denominator /= gc;
	return *this;
}

int64_t Fraction::distance()const
{
	return this->numerator.distance(this->denominator);
}

//Fraction Fraction::operator%(const Fraction& other)
//{
//	return Fraction();
//}

/*

Fraction& Fraction::operator++()
{
	// TODO: вставьте здесь оператор return
}

Fraction& Fraction::operator++(int)
{
	// TODO: вставьте здесь оператор return
}

Fraction& Fraction::operator--()
{
	// TODO: вставьте здесь оператор return
}

Fraction& Fraction::operator--(int)
{
	// TODO: вставьте здесь оператор return
}
*/

Fraction reciprocal(const Unlint& value)
{
	return Fraction(1, value, false);
}

Fraction reciprocal(const Fraction& value)
{
	return Fraction(value.denominator, value.numerator, false);
}

Fraction pow(const Fraction& value, const int& n)
{
	if (n > 0)
		return Fraction(pow(value.numerator, (uint32_t)n), pow(value.denominator, (uint32_t)n), false);
	if (n < 0)
	{
		if (value.denominator.zero())
			exit(ZERO_DIVISION_ERROR_CODE);
		else
			return Fraction(pow(value.denominator, (uint32_t)(-n)), pow(value.numerator, (uint32_t)(-n)), false);
	}
	return 1;
}

