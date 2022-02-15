#include "BitFrac.h"

class Unreal;
BitFrac::BitFrac(const Ubit& numerator, const Ubit& denominator, bool check)
{
	if (denominator.zero())
		exit(ZERO_DIVISION_ERROR_CODE);
	if (numerator.zero())
	{
		*this = 0;
		return;
	}

	if (check)
	{
		Ubit gc = gcd(numerator, denominator);
		this->numerator = numerator / gc;
		this->denominator = denominator / gc;
	}
	else
	{
		this->numerator = numerator;
		this->denominator = denominator;
	}
	this->numerator.set_sign(this->numerator.get_sign() ^ this->denominator.get_sign());
	this->denominator.set_sign(false);
}

BitFrac::BitFrac(const Ubit& value)
{
	this->numerator = value;
	this->denominator = 1;
}



BitFrac::BitFrac(const int& value)
{
	this->numerator = value;
	this->denominator = 1;
}

BitFrac::BitFrac()
{
	this->numerator = 0;
	this->denominator = 1;
}

BitFrac& BitFrac::operator=(const BitFrac& other)
{
	this->numerator = other.numerator;
	this->denominator = other.denominator;
	return *this;
}

bool BitFrac::operator==(const BitFrac& other)
{
	return this->numerator * other.denominator == this->denominator * other.numerator;
}

bool BitFrac::operator!=(const BitFrac& other)
{
	return this->numerator * other.denominator != this->denominator * other.numerator;
}

bool BitFrac::operator>(const BitFrac& other)
{
	return this->numerator * other.denominator > this->denominator * other.numerator;
}

bool BitFrac::operator>=(const BitFrac& other)
{
	return this->numerator * other.denominator >= this->denominator * other.numerator;
}

bool BitFrac::operator<(const BitFrac& other)
{
	return this->numerator * other.denominator < this->denominator* other.numerator;
}

bool BitFrac::operator<=(const BitFrac& other)
{
	return this->numerator * other.denominator <= this->denominator * other.numerator;
}

BitFrac BitFrac::operator*(const BitFrac& other)const
{
	return BitFrac(this->numerator * other.numerator, this->denominator * other.denominator);
}

BitFrac BitFrac::operator+(const BitFrac& other)const
{
	return BitFrac(this->numerator * other.denominator + this->denominator * other.numerator, this->denominator * other.denominator);
}

BitFrac BitFrac::operator-(const BitFrac& other)const
{
	return BitFrac(this->numerator * other.denominator - this->denominator * other.numerator, this->denominator * other.denominator);
}

BitFrac BitFrac::operator/(const BitFrac& other)const
{
	if (other.numerator.zero())
		exit(ZERO_DIVISION_ERROR_CODE);
	return BitFrac(this->numerator * other.denominator, this->denominator * other.numerator);
}


BitFrac BitFrac::operator-()const
{
	return BitFrac(-this->numerator, this->denominator, false);
}

BitFrac& BitFrac::operator+=(const BitFrac& other)
{
	this->numerator = this->numerator * other.denominator + this->denominator * other.numerator;
	this->denominator *= other.denominator;
	Ubit gc = gcd(this->numerator, this->denominator);
	this->numerator /= gc;
	this->denominator /= gc;
	return *this;
}

BitFrac& BitFrac::operator-=(const BitFrac& other)
{
	this->numerator = this->numerator * other.denominator - this->denominator * other.numerator;
	this->denominator *= other.denominator;
	Ubit gc = gcd(this->numerator, this->denominator);
	this->numerator /= gc;
	this->denominator /= gc;
	return *this;
}



BitFrac& BitFrac::operator*=(const BitFrac& other)
{
	this->numerator *= other.numerator;
	this->denominator *= other.denominator;
	Ubit gc = gcd(this->numerator, this->denominator);
	this->numerator /= gc;
	this->denominator /= gc;
	return *this;
}

int64_t BitFrac::distance()const
{
	return this->numerator.distance(this->denominator);
}

//BitFrac BitFrac::operator%(const BitFrac& other)
//{
//	return BitFrac();
//}

/*

BitFrac& BitFrac::operator++()
{
	// TODO: вставьте здесь оператор return
}

BitFrac& BitFrac::operator++(int)
{
	// TODO: вставьте здесь оператор return
}

BitFrac& BitFrac::operator--()
{
	// TODO: вставьте здесь оператор return
}

BitFrac& BitFrac::operator--(int)
{
	// TODO: вставьте здесь оператор return
}
*/

BitFrac reciprocal(const Ubit& value)
{
	return BitFrac(1, value, false);
}

BitFrac reciprocal(const BitFrac& value)
{
	return BitFrac(value.denominator, value.numerator, false);
}

BitFrac pow(const BitFrac& value, const int& n)
{
	if (n > 0)
		return BitFrac(pow(value.numerator, (uint32_t)n), pow(value.denominator, (uint32_t)n), false);
	if (n < 0)
	{
		if (value.denominator.zero())
			exit(ZERO_DIVISION_ERROR_CODE);
		else
			return BitFrac(pow(value.denominator, (uint32_t)(-n)), pow(value.numerator, (uint32_t)(-n)), false);
	}
	return 1;
}

