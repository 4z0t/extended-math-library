#include "BinInt.h"


char bin_int_length(uint32_t num)
{
	char i = 0;
	while (num) {
		num >>= 1; i++;
	}
	return i;
}

inline int64_t BinInt::distance() const
{
	return ((int64_t)(this->_len)) * sizeof(uint32_t) + bin_int_length(this->_num[this->_len - 1]);
}


int64_t BinInt::distance(const BinInt& other) const
{
	return this->distance() - other.distance();
}

inline BinInt::BinInt(const uint32_t& capacity, bool sign) : IntBase(capacity, sign) {}

BinInt  BinInt::abs_sum(const BinInt& other) const
{
	return (BinInt());
}

BinInt  BinInt::abs_sub(const BinInt& other) const
{
	return (BinInt());
}



inline BinInt::BinInt() : IntBase() {}

inline BinInt::BinInt(const BinInt& other) : IntBase(other) {}

BinInt::BinInt(const int8_t& value)
{
}

BinInt::BinInt(const uint8_t& value)
{
}

BinInt::BinInt(const int16_t& value)
{
}

BinInt::BinInt(const uint16_t& value)
{
}

BinInt::BinInt(const int32_t& value)
{
}

BinInt::BinInt(const uint32_t& value)
{
}

BinInt::BinInt(const int64_t& value)
{
}

BinInt::BinInt(const uint64_t& value)
{
}

BinInt  BinInt::operator*(const BinInt& other) const
{
	return BinInt();
}

BinInt  BinInt::operator+(const BinInt& other) const
{
	return BinInt();
}

BinInt  BinInt::operator-(const BinInt& other) const
{
	return BinInt();
}

BinInt  BinInt::operator/(const BinInt& other) const
{
	return BinInt();
}

BinInt  BinInt::operator%(const BinInt& other) const
{
	return BinInt();
}

BinInt& BinInt::operator=(const BinInt& other)
{
	return *this;
}

BinInt& BinInt::operator*=(const BinInt& other)
{
	return *this;
	// TODO: вставьте здесь оператор return
}

BinInt& BinInt::operator+=(const BinInt& other)
{
	return *this;
	// TODO: вставьте здесь оператор return
}

BinInt& BinInt::operator-=(const BinInt& other)
{
	return *this;
	// TODO: вставьте здесь оператор return
}

BinInt& BinInt::operator/=(const BinInt& other)
{
	return *this;
	// TODO: вставьте здесь оператор return
}

BinInt& BinInt::operator%=(const BinInt& other)
{
	return *this;
	// TODO: вставьте здесь оператор return
}

BinInt& BinInt::operator++()
{
	return *this;
	// TODO: вставьте здесь оператор return
}

BinInt BinInt::operator++(int)
{
	return BinInt();
}

BinInt& BinInt::operator--()
{
	return *this;
	// TODO: вставьте здесь оператор return
}

BinInt BinInt::operator--(int)
{
	return BinInt();
}

BinInt BinInt::operator-() const
{
	return BinInt();
}

#ifdef _INITIALIZER_LIST_
BinInt::BinInt(std::initializer_list<uint32_t> num, bool negative)
{

	if (this->_num)delete[]this->_num;
	this->_sign = negative;
	uint32_t  j = (this->_len = num.size());
	this->_capacity = this->_len;
	this->_num = new uint32_t[this->_len]{};
	for (uint32_t i : num)
	{
		this->_num[--j] = i;
	}
	this->normalize();
}
#endif


