#pragma once
#include"Ubit.h"
class BitFrac
{
	Ubit numerator;
	Ubit denominator;
public:
	BitFrac(const Ubit& numerator, const Ubit& denominator, bool check = true);
	BitFrac();
	BitFrac(const Ubit& value);

	BitFrac(const int& value);
	BitFrac& operator=(const BitFrac& other);

	bool operator==(const BitFrac& other);
	bool operator!=(const BitFrac& other);
	bool operator>(const BitFrac& other);
	bool operator>=(const BitFrac& other);
	bool operator<(const BitFrac& other);
	bool operator<=(const BitFrac& other);

	BitFrac operator*(const BitFrac& other)const;
	BitFrac operator+(const BitFrac& other)const;
	BitFrac operator-(const BitFrac& other)const;
	BitFrac operator/(const BitFrac& other)const;
	//BitFrac operator%(const BitFrac& other);

	//Ubit operator*(const int &value);

	BitFrac operator-()const;

	BitFrac& operator+=(const BitFrac& other);
	BitFrac& operator-=(const BitFrac& other);
	BitFrac& operator*=(const BitFrac& other);

	int64_t distance()const;
	/*

	BitFrac& operator++();
	BitFrac& operator++(int);
	BitFrac& operator--();
	BitFrac& operator--(int);
	*/
	friend BitFrac reciprocal(const BitFrac& value);
	friend BitFrac pow(const BitFrac& value, const int& n);
#ifdef UFLOAT_H
	BitFrac(const Ufloat& value);
	Ufloat calculate(const unsigned int& precision = Ufloat::get_precision())const;
	Ufloat operator~()const;//calculates Ufloat value with current precision
#endif //Ufloat_H

#ifdef FRACTION_H
	Fraction convert();
#endif // FRACTION_H


};
BitFrac reciprocal(const Ubit& value);


#ifdef UFLOAT_H
Ufloat BitFrac::calculate(const uint32_t& precision)const
{
	return Ufloat(this->numerator, precision) / this->denominator;
}
BitFrac::BitFrac(const Ufloat& value)
{
	*this = BitFrac(value.number, Ubit(1).movecells(value.precision));
}
Ufloat BitFrac::operator~()const
{
	return Ufloat(this->numerator) / this->denominator;
}
#endif //Ufloat_H

#ifdef FRACTION_H
Fraction BitFrac::convert()
{
	return Fraction(this->numerator.convert(),this->denominator.convert());
}
#endif