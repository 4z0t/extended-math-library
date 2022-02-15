#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#define ZERO_DIVISION_ERROR_CODE			100
class Frac
{

	int32_t numerator;
	int32_t denominator;
public:
	Frac(const int32_t& numerator, const int32_t& denominator, bool check = true);
	Frac();
	Frac(const int32_t& value);

	Frac& operator=(const Frac& other);

	bool operator==(const Frac& other);
	bool operator!=(const Frac& other);
	bool operator>(const Frac& other);
	bool operator>=(const Frac& other);
	bool operator<(const Frac& other);
	bool operator<=(const Frac& other);

	Frac operator*(const Frac& other)const;
	Frac operator+(const Frac& other)const;
	Frac operator-(const Frac& other)const;
	Frac operator/(const Frac& other)const;
	//Frac operator%(const Frac& other);

	//int32_t operator*(const int &value);

	Frac operator-()const;

	Frac& operator+=(const Frac& other);
	Frac& operator-=(const Frac& other);
	Frac& operator*=(const Frac& other);
	Frac& operator/=(const Frac& other);

	
	/*
	Frac& operator-=(const Frac& other);

	Frac& operator++();
	Frac& operator++(int);
	Frac& operator--();
	Frac& operator--(int);
	*/
	friend Frac reciprocal(const Frac& value);
	//friend Frac pow(const Frac& value, const int& n);
	double operator~()const;


#ifdef _IOSTREAM_
	friend inline std::ostream& operator<<(std::ostream& os, const Frac& value)
	{
		if (value.denominator == 1)
			return os << value.numerator;
		else
			return os << value.numerator << '/' << value.denominator;
	}
#endif

};

int32_t gcd(const int32_t& value1, const int32_t& value2);
Frac reciprocal(const int32_t& value);

