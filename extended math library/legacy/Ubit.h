#pragma once
#include <stdint.h>
#include <stdlib.h>
#define ZERO_DIVISION_ERROR_CODE			100
#define NEGATIVE_ARGUMENT_ERROR_CODE		101
#define ZERO_ARGUMENT_ERROR_CODE			102
#define CANT_OPEN_FILE						103

#define POS									1
#define NEG									-1
#define EQU									0
const uint32_t last_bit = 0x80000000;
const uint32_t mask_last_bit = 0x7fffffff;
const uint32_t mask = 0xffffffff;
const uint32_t len_mask = 0xfffffffe;

class Ufloat;
class BitFrac;

typedef struct sum
{
	uint32_t rest;
	uint32_t num;
}sum;
char num_len(uint32_t num);
sum smart_sum(const uint32_t& n1, const uint32_t& n2);

class Ubit
{
	uint32_t len_sign;//first bit represents sign
	uint32_t* num;

	Ubit(const uint32_t& len, bool negative);

	Ubit addition(const Ubit& other,bool sign)const;//basic method |first|>=|second|
	Ubit substruction(const Ubit& other, bool sign)const;//basic method |first|>=|second|

	Ubit& antidrain();
	inline bool get_sign()const;
	inline uint32_t get_len()const;
	void set_sign(bool sign);

	int64_t distance(const Ubit& other)const;
	Ubit cut(const uint32_t& length)const;
	Ubit& cutthis(const uint32_t& length);

	bool abs_compare(const Ubit& other)const;
public:
	Ubit();
	~Ubit();

	Ubit(const Ubit& other);

	Ubit(const int8_t& value);
	Ubit(const uint8_t& value);

	Ubit(const int16_t& value);
	Ubit(const uint16_t& value);

	Ubit(const int32_t& value);
	Ubit(const uint32_t& value);

	Ubit(const int64_t& value);
	Ubit(const uint64_t& value);

	bool operator==(const Ubit& other)const;
	bool operator!=(const Ubit& other)const;
	bool operator>(const Ubit& other)const;
	bool operator>=(const Ubit& other)const;
	bool operator<(const Ubit& other)const;
	bool operator<=(const Ubit& other)const;

	explicit operator int8_t()const;
	explicit operator int16_t()const;
	explicit operator int32_t()const;
	explicit operator int64_t()const;
	explicit operator uint8_t()const;
	explicit operator uint16_t()const;
	explicit operator uint32_t()const;
	explicit operator uint64_t()const;

	explicit operator bool()const;

	Ubit operator*(const Ubit& other)const;
	Ubit operator+(const Ubit& other)const;
	Ubit operator-(const Ubit& other)const;
	Ubit operator/(const Ubit& other)const;
	Ubit operator%(const Ubit& other)const;

	Ubit& operator=(const Ubit& other);

	Ubit& operator*=(const Ubit& other);
	Ubit& operator+=(const Ubit& other);
	Ubit& operator-=(const Ubit& other);
	Ubit& operator/=(const Ubit& other);
	Ubit& operator%=(const Ubit& other);

	Ubit operator-()const;
	Ubit& operator++();
	Ubit operator++(int);

	Ubit operator <<(const uint32_t& length) const;

	Ubit& operator <<=(const uint32_t& times);

	Ubit operator|(const Ubit& other)const;
	Ubit operator&(const Ubit& other)const;
	Ubit operator^(const Ubit& other)const;
	Ubit operator~()const;//very strange thing

	Ubit& operator|=(const Ubit& other);
	Ubit& operator&=(const Ubit& other);
	Ubit& operator^=(const Ubit& other);

	Ubit& movethiscells(const uint32_t& length);
	Ubit movecells(const uint32_t& length)const;
	friend Ubit abs(const Ubit& value);
	void print()const;

	bool zero()const;
	
	friend class Ufloat;
	friend class BitFrac;

#ifdef UNLINT_H
	Unlint convert()const;
#endif

};


#ifdef UNLINT_H
Unlint Ubit::convert()const
{
	Unlint result = this->num[0];
	if (this->get_len() != 1)
	{
		Unlint mult = 1;
		mult += 0xffffffff;
		Unlint two32 = mult;
		for (uint32_t i = 1; i < this->get_len(); i++)
		{
			result += mult * this->num[i];
			mult *= two32;
		}
	}
	return result;
}
#endif
Ubit gcd(const Ubit& value1, const Ubit& value2);
Ubit pow(const Ubit& other, const uint32_t& n);

typedef Ubit Int;