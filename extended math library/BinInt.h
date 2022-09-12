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

public:
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

#endif // !BININT_H
