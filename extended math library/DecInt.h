#pragma once
#include "IntBase.h"
#include <cstdlib>
#ifndef DECINT_H
#define DECINT_H

constexpr u32 pow10(const u32 value)
{
	switch (value)
	{
	case 0:
		return 1u;
	case 1:
		return 10u;
	case 2:
		return 100u;
	case 3:
		return 1'000u;
	case 4:
		return 10'000u;
	case 5:
		return 100'000u;
	case 6:
		return 1000'000u;
	case 7:
		return 10'000'000u;
	case 8:
		return 100'000'000u;
	case 9:
		return 1000'000'000u;
	default:
		assert(value < 10);
		return 0;
	}
}



class DecInt :
	public IntBase<DecInt>
{
	int64_t distance()const override;
	int64_t distance(const DecInt& other)const override;
	DecInt(const u32& capacity, bool sign) : IntBase(capacity, sign) {}
	DecInt _MOVE_BIGINT_REF abs_sum(const DecInt& other)const;
	DecInt _MOVE_BIGINT_REF abs_sub(const DecInt& other)const;


public:
	DecInt _MOVE_BIGINT_REF move10(const u32& times) const;
	DecInt& movethis10(const u32& times);
	static constexpr u32 milrd = 1'000'000'000;
	static int dec_int_length(const u32& num);

	DecInt() : IntBase() {}
	DecInt(const DecInt& other) : IntBase(other) {}

	DecInt(const int8_t& value);
	DecInt(const uint8_t& value);

	DecInt(const int16_t& value);
	DecInt(const uint16_t& value);

	DecInt(const int32_t& value);
	DecInt(const u32& value);

	DecInt(const int64_t& value);
	DecInt(const uint64_t& value);


	DecInt _MOVE_BIGINT_REF operator*(const DecInt& other)const override;
	DecInt _MOVE_BIGINT_REF operator+(const DecInt& other)const override;
	DecInt _MOVE_BIGINT_REF operator-(const DecInt& other)const override;
	DecInt _MOVE_BIGINT_REF operator/(const DecInt& other)const override;
	DecInt _MOVE_BIGINT_REF operator%(const DecInt& other)const override;

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


#if _HAS_CXX17 
	DecInt(DecInt&& other) noexcept :IntBase(std::move(other)) {};
	DecInt& operator=(DecInt&& other) noexcept{ IntBase::operator=(std::move(other)); return *this; };
#endif

#ifdef _IOSTREAM_
	void print(bool sep)const;
	friend std::ostream& operator<<(std::ostream& os, const DecInt& value);
#endif

#ifdef _INITIALIZER_LIST_
	DecInt(std::initializer_list<u32> num) :DecInt(num, false) {}
	DecInt(std::initializer_list<u32> num, bool negative);
#endif
	friend class IntBase<DecInt>;
};

#endif

