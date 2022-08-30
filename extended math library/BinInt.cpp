#include "BinInt.h"

int64_t BinInt::distance() const
{
	return int64_t();
}

int64_t BinInt::distance(const BinInt& other) const
{
	return int64_t();
}

inline BinInt::BinInt(const uint32_t& capacity, bool sign) : IntBase(capacity, sign) {}

BinInt BinInt::abs_sum(const BinInt& other) const
{
	return BinInt();
}

BinInt BinInt::abs_sub(const BinInt& other) const
{
	return BinInt();
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

BinInt BinInt::operator*(const BinInt& other) const
{
	return BinInt();
}

BinInt BinInt::operator+(const BinInt& other) const
{
	return BinInt();
}

BinInt BinInt::operator-(const BinInt& other) const
{
	return BinInt();
}

BinInt BinInt::operator/(const BinInt& other) const
{
	return BinInt();
}

BinInt BinInt::operator%(const BinInt& other) const
{
	return BinInt();
}

BinInt& BinInt::operator=(const BinInt& other)
{
	// TODO: �������� ����� �������� return
}

BinInt& BinInt::operator*=(const BinInt& other)
{
	// TODO: �������� ����� �������� return
}

BinInt& BinInt::operator+=(const BinInt& other)
{
	// TODO: �������� ����� �������� return
}

BinInt& BinInt::operator-=(const BinInt& other)
{
	// TODO: �������� ����� �������� return
}

BinInt& BinInt::operator/=(const BinInt& other)
{
	// TODO: �������� ����� �������� return
}

BinInt& BinInt::operator%=(const BinInt& other)
{
	// TODO: �������� ����� �������� return
}

BinInt& BinInt::operator++()
{
	// TODO: �������� ����� �������� return
}

BinInt BinInt::operator++(int)
{
	return BinInt();
}

BinInt& BinInt::operator--()
{
	// TODO: �������� ����� �������� return
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
	this->cut_zeros();
}
#endif


