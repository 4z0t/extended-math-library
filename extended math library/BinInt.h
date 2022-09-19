#pragma once
#ifndef BININT_H
#define BININT_H
#include "IntBase.h"
class BinInt :
	public IntBase<BinInt>
{
	int64_t distance()const override;
	int64_t distance(const BinInt& other)const override;
	BinInt(const uint32_t& capacity, bool sign);
	BinInt  abs_sum(const BinInt& other)const;
	BinInt  abs_sub(const BinInt& other)const;


	typedef struct _sum
	{
		uint32_t rest;
		uint32_t num;

	};


	static _sum smart_sum(const uint32_t& n1, const uint32_t& n2)
	{
		_sum result;
		result.num = n1 + n2;
		result.rest = (result.num < n1) ? 1 : 0;
		return result;
	}

public:

	static u32 bin_int_length(uint32_t num);

	static const uint32_t mask = 0xffffffff;

	BinInt();
	BinInt(const BinInt& other);

	BinInt(const int8_t& value);
	BinInt(const uint8_t& value);

	BinInt(const int16_t& value);
	BinInt(const uint16_t& value);

	BinInt(const int32_t& value);
	BinInt(const uint32_t& value);

	BinInt(const int64_t& value);
	BinInt(const uint64_t& value);


	BinInt  operator*(const BinInt& other)const override;
	BinInt  operator+(const BinInt& other)const override;
	BinInt  operator-(const BinInt& other)const override;
	BinInt  operator/(const BinInt& other)const override;
	BinInt  operator%(const BinInt& other)const override;

	BinInt& operator=(const BinInt& other) override;

	BinInt& operator*=(const BinInt& other) override;
	BinInt& operator+=(const BinInt& other) override;
	BinInt& operator-=(const BinInt& other) override;
	BinInt& operator/=(const BinInt& other) override;
	BinInt& operator%=(const BinInt& other) override;

	BinInt& operator++()override;
	BinInt operator++(int)override;
	BinInt& operator--()override;
	BinInt operator--(int)override;
	BinInt operator-()const override;


#if _HAS_CXX17 
	BinInt(BinInt&& other) noexcept :IntBase(std::move(other)) {};
	inline BinInt& operator=(BinInt&& other) noexcept { IntBase::operator=(std::move(other)); return *this; };
#endif

#ifdef FLOAT_BASE_H
	friend class FloatBase< BinInt>;
#ifdef _IOSTREAM_
	friend std::ostream& operator<<(std::ostream& os, const FloatBase<BinInt>& value);
#endif
#endif


#ifdef _IOSTREAM_
	void print(bool sep)const;
	friend std::ostream& operator<<(std::ostream& os, const BinInt& value);
#endif

#ifdef _INITIALIZER_LIST_
	BinInt(std::initializer_list<uint32_t> num) : BinInt(num, false) {}
	BinInt(std::initializer_list<uint32_t> num, bool negative);
#endif
	friend class IntBase<BinInt>;

private:

	bool _inverted = false;

};
#ifdef FLOAT_BASE_H
typedef FloatBase< BinInt> BinFloat;
#endif
#endif // !BININT_H
