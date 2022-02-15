#pragma once
#define UFLOAT_H
#include<iostream>
//#include "Unlint.h"
#include"Ubit.h"

class Ufloat
{
public:
	static const uint32_t basic_precision = 10;
	static uint32_t settable_precision;//FIXIT private static member
	static bool isset;//FIXIT private static member

	Ufloat();
	~Ufloat();
	Ufloat(const Ufloat& other);
	Ufloat(const Ubit& other);
	Ufloat(const int& value);
	Ufloat(const float& value);
	Ufloat(const double& value);
	Ufloat(const Ubit& other, const uint32_t& accur, bool domove = true);

	Ufloat operator*(const Ufloat& other)const;
	Ufloat operator*(const uint32_t& other)const;
	Ufloat operator+(const Ufloat& other)const;
	Ufloat operator-(const Ufloat& other)const;

	template<class T>
	Ufloat operator/(const T& other)const;
	Ufloat operator/(const Ufloat& other)const;
	Ufloat operator/(const Ubit& other)const;
	Ufloat operator/(const int& other)const;

	explicit operator double()const;
	explicit operator float()const;

	Ufloat& operator+=(const Ufloat& other);
	Ufloat& operator+=(const Ubit& other);
	Ufloat& operator+=(const int& other);

	Ufloat& operator-=(const Ufloat& other);
	Ufloat& operator-=(const Ubit& other);
	Ufloat& operator-=(const int& other);

	Ufloat& operator/=(const Ufloat& other);
	Ufloat& operator/=(const Ubit& other);
	Ufloat& operator/=(const int& other);

	Ufloat& operator*=(const Ufloat& other);
	Ufloat& operator*=(const Ubit& other);
	Ufloat& operator*=(const int& other);

	Ufloat& operator=(const Ufloat& other);

	Ufloat operator-()const;

	bool operator==(const Ufloat& other)const;
	bool operator!=(const Ufloat& other)const;
	bool operator>(const Ufloat& other)const;
	bool operator<(const Ufloat& other)const;
	bool operator>=(const Ufloat& other)const;
	bool operator<=(const Ufloat& other)const;

	friend Ufloat sqrt(const Ufloat& value);
	friend Ufloat abs(const Ufloat& value);
	friend Ufloat ln(const Ufloat& value);
	friend Ufloat operator*(const uint32_t& value, const Ufloat& other);

	static void set_precision(const uint32_t& accur);
	static uint32_t get_precision();

	friend class BitFrac;
#ifdef FRACTION_H
	Fraction convert()const;
#endif
#ifdef _IOSTREAM_
	void print()const;
	friend std::ostream& operator<<(std::ostream& os, const Ufloat& value);
#endif
#ifdef _FSTREAM_
	void printinfile(std::string filename);
	void readbytesfromfile(std::string filename);
	void writebytestofile(std::string filename);
	void writebytestofile(std::string filename)const;
	Ufloat(std::string filename);
#endif

private:
	uint32_t precision;
	Ubit number;
};



