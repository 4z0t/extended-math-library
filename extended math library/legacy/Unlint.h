
#pragma once
#ifndef UNLINT_H
#define UNLINT_H
#define ZERO_DIVISION_ERROR_CODE			100
#define NEGATIVE_ARGUMENT_ERROR_CODE		101
#define ZERO_ARGUMENT_ERROR_CODE			102
#define CANT_OPEN_FILE						103
#define CONVERT_ERROR true
#define CONVERT_BY_BITS true
#define CANT_CONVERT_TO_UINT8_ERROR_CODE	201
#define CANT_CONVERT_TO_INT8_ERROR_CODE		202
#define CANT_CONVERT_TO_UINT16_ERROR_CODE	203
#define CANT_CONVERT_TO_INT16_ERROR_CODE	204
#define CANT_CONVERT_TO_UINT32_ERROR_CODE	205
#define CANT_CONVERT_TO_INT32_ERROR_CODE	206
#define CANT_CONVERT_TO_UINT64_ERROR_CODE	207
#define CANT_CONVERT_TO_INT64_ERROR_CODE	208
#include<iostream>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
class Fraction;
class Unreal;

int length_int(const uint32_t& num);
uint32_t pow10(const int& value);
uint32_t niv(const uint32_t& num, const uint32_t& index);

const uint32_t milrd = 1'000'000'000;

class Unlint
{
private:
	bool negative = false;
	uint32_t len;
	uint32_t* num;

	Unlint move10(const uint32_t& times)const;
	Unlint movecells(const uint32_t& length)const;
	Unlint cut(const uint32_t& length)const;

	Unlint& movethis10(const uint32_t& times);
	Unlint& movethiscells(const uint32_t& length);
	Unlint& cutthis(const uint32_t& length);

	bool operator>>(const Unlint& other)const;
	bool operator<<(const Unlint& other)const;

	void extend();
	Unlint& antidrain();

	int64_t distance(const Unlint& other)const;

public:
	int64_t distance()const;
	static Unlint ten(const uint32_t& power);
	bool zero()const;
	uint64_t getsize()const;

	Unlint();
	~Unlint();
	Unlint(const uint32_t& num_len, bool negative);
	Unlint(const uint32_t* num, const uint32_t& len, bool negative = false);

	Unlint(const Unlint& other);

	Unlint(const int8_t& value);
	Unlint(const uint8_t& value);

	Unlint(const int16_t& value);
	Unlint(const uint16_t& value);

	Unlint(const int32_t& value);
	Unlint(const uint32_t& value);

	Unlint(const int64_t& value);
	Unlint(const uint64_t& value);

	bool operator==(const Unlint& other)const;
	bool operator!=(const Unlint& other)const;
	bool operator>(const Unlint& other)const;
	bool operator>=(const Unlint& other)const;
	bool operator<(const Unlint& other)const;
	bool operator<=(const Unlint& other)const;


	explicit operator int8_t()const;
	explicit operator int16_t()const;
	explicit operator int32_t()const;
	explicit operator int64_t()const;
	explicit operator uint8_t()const;
	explicit operator uint16_t()const;
	explicit operator uint32_t()const;
	explicit operator uint64_t()const;

	explicit operator double()const;
	explicit operator float()const;
	explicit operator bool()const;

	Unlint operator*(const Unlint& other)const;
	Unlint operator+(const Unlint& other)const;
	Unlint operator-(const Unlint& other)const;
	Unlint operator/(const Unlint& other)const;
	Unlint operator%(const Unlint& other)const;

	Unlint& operator=(const Unlint& other);

	Unlint& operator*=(const Unlint& other);
	Unlint& operator+=(const Unlint& other);
	Unlint& operator-=(const Unlint& other);
	Unlint& operator/=(const Unlint& other);
	Unlint& operator%=(const Unlint& other);

	Unlint& operator++();
	Unlint operator++(int);
	Unlint& operator--();
	Unlint operator--(int);
	Unlint operator-()const;

	friend class Fraction;
	friend class Unreal;
	
	//friend Unlint ten(const uint32_t& power);
	friend Unlint abs(const Unlint& value);
	friend Unreal abs(const Unreal& value);
	friend Unlint sign(const Unlint& value);
	friend Unlint sqrt(const Unlint& value);
	friend char* cstring(const Unlint& value);
	friend char* bytes(const Unlint& value);

#ifdef _IOSTREAM_
	void print()const;
	friend std::ostream& operator<<(std::ostream& os, const Unlint& value);
	friend std::ostream& operator<<(std::ostream& os, const Unreal& value);//HOW IT WORKS??????
#endif
#ifdef _FSTREAM_
	void printinfile(std::string filename);
	void readbytesfromfile(std::string filename);
	void writebytestofile(std::string filename);
	void writebytestofile(std::string filename)const;
	Unlint(std::string filename);
#endif

#ifdef _INITIALIZER_LIST_
	Unlint(std::initializer_list<uint32_t> num)
	{
		uint32_t  j = (this->len = num.size());
		this->num = new uint32_t[this->len]{};
		for (uint32_t i : num)
			this->num[--j] = i;
	}

	Unlint(std::initializer_list<uint32_t> num, bool negative)
	{
		this->negative = negative;
		uint32_t  j = (this->len = num.size());
		this->num = new uint32_t[this->len]{};
		for (uint32_t i : num)
			this->num[--j] = i;
	}
#endif
};

Unlint gcd(const Unlint& value1, const Unlint& value2);
Unlint pow(const Unlint& other, const uint32_t& n);
Unlint sqr(const Unlint& other);
char getcharfromint(const uint32_t& value, const char& index);

//Unlint ten(const uint32_t& power)
//{
//	return Unlint(pow10(power % 9)).movecells(power/9);
//}


#endif // UNLINT_H
