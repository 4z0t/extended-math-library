#pragma once
#include "IntBase.h"
#include <cstdlib>
#ifndef DECINT_H
#define DECINT_H

class DecInt :
	public IntBase<DecInt>
{
	int64_t distance()const override;
	int64_t distance(const DecInt& other)const override;
	DecInt(const uint32_t& capacity, bool sign) : IntBase(capacity, sign) {}
	DecInt abs_sum(const DecInt& other)const;
	DecInt abs_sub(const DecInt& other)const;
	
public:
	static constexpr uint32_t milrd = 1'000'000'000;
	static int dec_int_length(const uint32_t& num);

	DecInt() : IntBase() {}
	DecInt(const DecInt& other) : IntBase(other) {}

	DecInt(const int8_t& value);
	DecInt(const uint8_t& value);

	DecInt(const int16_t& value);
	DecInt(const uint16_t& value);

	DecInt(const int32_t& value);
	DecInt(const uint32_t& value);

	DecInt(const int64_t& value);
	DecInt(const uint64_t& value);


	DecInt operator*(const DecInt& other)const override;
	DecInt operator+(const DecInt& other)const override;
	DecInt operator-(const DecInt& other)const override;
	DecInt operator/(const DecInt& other)const override;
	DecInt operator%(const DecInt& other)const override;

	DecInt& operator=(const DecInt& other) override;

	DecInt& operator*=(const DecInt& other) override;
	DecInt& operator+=(const DecInt& other) override;
	DecInt& operator-=(const DecInt& other) override;
	DecInt& operator/=(const DecInt& other) override;
	DecInt& operator%=(const DecInt& other) override;

	DecInt& operator++()override;
	DecInt operator++(int)override;
	DecInt& operator--()override;
	DecInt operator--(int)override;
	DecInt operator-()const override;







#ifdef _IOSTREAM_
	void print(bool sep)const;
	friend std::ostream& operator<<(std::ostream& os, const DecInt& value);
#endif

#ifdef _INITIALIZER_LIST_
	DecInt(std::initializer_list<uint32_t> num) :DecInt(num, false) {}
	DecInt(std::initializer_list<uint32_t> num, bool negative);
#endif
	friend class IntBase<DecInt>;
};

#endif

