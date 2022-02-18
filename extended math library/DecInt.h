#pragma once
#include "IntBase.h"
#ifndef DECINT_H
#define DECINT_H

class DecInt :
	public IntBase<DecInt>
{
public:
	static const uint32_t milrd = 1'000'000'000;
	static int dec_int_length(const uint32_t& num);

	DecInt() : IntBase() {}
	DecInt(const uint32_t& capacity, bool sign) :IntBase(capacity, sign) {}
	DecInt(const DecInt& other);
#ifdef _IOSTREAM_
	void print(bool sep)const;
	friend std::ostream& operator<<(std::ostream& os, const DecInt& value);
#endif

#ifdef _INITIALIZER_LIST_
	DecInt(std::initializer_list<uint32_t> num) :DecInt(num, false) {}

	DecInt(std::initializer_list<uint32_t> num, bool negative)
	{
		if (this->num)delete[]this->num;
		this->sign = negative;
		this->capacity = this->len;
		uint32_t  j = (this->len = num.size());
		this->num = new uint32_t[this->len]{};
		for (uint32_t i : num)
			this->num[--j] = i;
	}
#endif
};

#endif

