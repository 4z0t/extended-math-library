
#pragma once
#include "Unlint.h"
#ifndef FRACTION_H
#define FRACTION_H
class Unreal;
class Fraction
{
	Unlint numerator;
	Unlint denominator;
public:
	Fraction(const Unlint& numerator, const Unlint& denominator, bool check = true);
	Fraction();
	Fraction(const Unlint& value);

	Unlint get_numerator()
	{
		return numerator;
	}
	Unlint get_denominator()
	{
		return denominator;
	}

	Fraction(const int& value);
	Fraction& operator=(const Fraction& other);

	bool operator==(const Fraction& other);
	bool operator!=(const Fraction& other);
	bool operator>(const Fraction& other);
	bool operator>=(const Fraction& other);
	bool operator<(const Fraction& other);
	bool operator<=(const Fraction& other);

	Fraction operator*(const Fraction& other)const;
	Fraction operator+(const Fraction& other)const;
	Fraction operator-(const Fraction& other)const;
	Fraction operator/(const Fraction& other)const;
	//Fraction operator%(const Fraction& other);

	//Unlint operator*(const int &value);

	Fraction operator-()const;

	Fraction& operator+=(const Fraction& other);
	Fraction& operator-=(const Fraction& other);
	Fraction& operator*=(const Fraction& other);
	Fraction& operator/=(const Fraction& other);

	int64_t distance()const;
	/*
	Fraction& operator-=(const Fraction& other);

	Fraction& operator++();
	Fraction& operator++(int);
	Fraction& operator--();
	Fraction& operator--(int);
	*/
	friend Fraction reciprocal(const Fraction& value);
	friend Fraction pow(const Fraction& value, const int& n);
#ifdef UNREAL_H
	Fraction(const Unreal& value);
	Unreal calculate(const unsigned int& precision = Unreal::get_precision())const;
	Unreal operator~()const;//calculates unreal value with current precision

#ifdef _IOSTREAM_
	friend inline std::ostream& operator<<(std::ostream& os, const Fraction& value)
	{
		return os << Unreal(value.numerator) / value.denominator;
	}
#endif
#endif //UNREAL_H


};
Fraction reciprocal(const Unlint& value);



#ifdef UNREAL_H
Unreal Fraction::calculate(const uint32_t& precision)const
{
	return Unreal(this->numerator, precision) / this->denominator;
}
Fraction::Fraction(const Unreal& value)
{
	*this = Fraction(value.number, Unlint(1).movecells(value.precision));
}
Unreal Fraction::operator~()const//idk
{
	return Unreal(this->numerator) / this->denominator;
}
#endif
#endif