
#pragma once
#include "Unlint.h"

#ifndef UNREAL_H
#define UNREAL_H


class Fraction;

class Unreal
{
public:

	static const uint32_t basic_precision = 10;
	static uint32_t settable_precision;//FIXIT private static member
	static bool isset;//FIXIT private static member

	Unreal();
	~Unreal();
	Unreal(const Unreal& other);
	Unreal(const Unlint& other);
	Unreal(const int& value);
	Unreal(const float& value);
	Unreal(const double& value);
	Unreal(const Unlint& other, const uint32_t& accur, bool domove = true);
	
	Unreal operator*(const Unreal& other)const;
	Unreal operator*(const uint32_t& other)const;
	Unreal operator+(const Unreal& other)const;
	Unreal operator-(const Unreal& other)const;

	template<class T>
	Unreal operator/(const T& other)const;
	Unreal operator/(const Unreal& other)const;
	Unreal operator/(const Unlint& other)const;
	Unreal operator/(const int& other)const;

	explicit operator double()const;
	explicit operator float()const;

	Unreal& operator+=(const Unreal& other);
	Unreal& operator+=(const Unlint& other);
	Unreal& operator+=(const int& other);

	Unreal& operator-=(const Unreal& other);
	Unreal& operator-=(const Unlint& other);
	Unreal& operator-=(const int& other);

	Unreal& operator/=(const Unreal& other);
	Unreal& operator/=(const Unlint& other);
	Unreal& operator/=(const int& other);

	Unreal& operator*=(const Unreal& other);
	Unreal& operator*=(const Unlint& other);
	Unreal& operator*=(const int& other);

	Unreal& operator=(const Unreal& other);

	Unreal operator-()const;

	bool operator==(const Unreal& other)const;
	bool operator!=(const Unreal& other)const;
	bool operator>(const Unreal& other)const;
	bool operator<(const Unreal& other)const;
	bool operator>=(const Unreal& other)const;
	bool operator<=(const Unreal& other)const;

	friend class Fraction;
	friend Unreal abs(const Unreal& value);
	friend Unreal ln(const Unreal& value);
	friend Unreal operator*(const uint32_t& value, const Unreal& other);

	static void set_precision(const uint32_t& accur);
	static uint32_t get_precision();

#ifdef _IOSTREAM_
	void print()const;
	friend std::ostream& operator<<(std::ostream& os, const Unreal& value);//why i have to call it here and in Unlint?
#endif
#ifdef _FSTREAM_
	void printinfile(std::string filename);
	void readbytesfromfile(std::string filename);
	void writebytestofile(std::string filename);
	void writebytestofile(std::string filename)const;
	Unreal(std::string filename);
#endif

private:
	uint32_t precision;
	Unlint number;
};

Unreal sqrt(const Unreal& value);
Unreal pow(const Unreal& other, const uint32_t& n);




//template<class T>
// Unreal Unreal::operator/(const T& other) const
//{
//	return Unreal(this->number / other, this->precision, false);
//}
//
//template<>
// Unreal Unreal::operator/(const Unreal& other) const
//{
//	return Unreal(((this->number.movecells(other.precision)) / other.number), this->precision, false);
//}

#endif // UNREAL_H
