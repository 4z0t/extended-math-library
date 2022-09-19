#include "BinInt.h"


u32 BinInt::bin_int_length(uint32_t num)
{
	u32 i = 0;
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
	_sum n;
	u32 rest = 0;

	if (this->_len >= other._len)
	{
		BinInt result(this->_len + 1, this->_sign);
		for (u32 i = 0; i < this->_len; i++) {
			if (i < other._len)
			{
				_sum s = BinInt::smart_sum(this->_num[i], other._num[i]);
				if (s.num == mask && rest)
				{
					result._num[i] = 0;
					rest = 1;
					continue;
				}
				result._num[i] = rest + s.num;
				rest = s.rest;
				continue;
			}
			else
			{
				if (this->_num[i] == mask && rest)
				{
					result._num[i] = 0;
					rest = 1;
					continue;
				}
				result._num[i] = this->_num[i] + rest;
			}
			rest = 0;
		}
		result._num[this->_len] = rest;
		return  result.cut_zeros();

	}
	else
	{
		return other.abs_sum(*this);
	}
}

BinInt  BinInt::abs_sub(const BinInt& other) const
{
	int cmp_res = this->abs_compare(other);
	if (cmp_res == GREATER)
	{
		BinInt result = *this;
		for (u32 i = 0; i < other._len; i++)
			if (result._num[i] >= other._num[i])
			{
				result._num[i] -= other._num[i];
			}
			else
			{
				u32 j = i + 1;
				while (result._num[j] == 0)
				{
					result._num[j++] = mask;
					if (j == result._len)
						break;
				}
				result._num[j] -= 1;
				result._num[i] += (~other._num[i]) + 1;
			}
		return result.normalize();
	}
	else if (cmp_res == LESS)
	{
		BinInt result(other);
		for (u32 i = 0; i < this->_len; i++)
			if (result._num[i] >= this->_num[i])
			{
				result._num[i] -= this->_num[i];
			}
			else
			{
				u32 j = i + 1;
				while (result._num[j] == 0)
				{
					result._num[j++] = mask;
					if (j == result._len)
						break;
				}
				result._num[j] -= 1;
				result._num[i] += (~this->_num[i]) + 1;
			}
		result._sign = !other._sign;
		return result.normalize();
	}
	else
	{
		return BinInt(0);
	}

}



inline BinInt::BinInt() : IntBase() {}

inline BinInt::BinInt(const BinInt& other) : IntBase(other) {}

BinInt::BinInt(const int8_t& value) :BinInt(int32_t(value))
{
}
BinInt::BinInt(const uint8_t& value) :BinInt(int32_t(value))
{
}
BinInt::BinInt(const int16_t& value) :BinInt(int32_t(value))
{
}
BinInt::BinInt(const uint16_t& value) :BinInt(int32_t(value))
{
}
BinInt::BinInt(const int32_t& value) :BinInt(1, false)
{
	this->_sign = (value < 0);


	this->_len = 1;
	this->_num[0] = abs(value);

}
BinInt::BinInt(const uint32_t& value) :BinInt(1, false)
{

	this->_len = 1;
	this->_num[0] = value;

}
BinInt  BinInt::operator*(const BinInt& other) const
{

	uint64_t  b;
	_sum s; uint32_t rest;
	BinInt result(this->_len + other._len + 1, this->_sign != other._sign);
	for (u32 i = 0; i < this->_len; i++)
		for (u32 j = 0; j < other._len; j++)
		{
			if (this->_num[i] && other._num[j])
			{
				b = (uint64_t)this->_num[i] * other._num[j];
				s = smart_sum(result._num[i + j], (u32)b);
				result._num[i + j] = s.num;
				rest = s.rest;
				s = smart_sum(result._num[i + j + 1], (b >> 32));
				result._num[i + j + 1] = s.num + rest;
				if (s.rest)result._num[i + j + 2]++;
			}
		}
	return result.normalize();
}


BinInt  BinInt::operator+(const BinInt& other) const
{
	if (this->_sign == other._sign)
	{
		return (this->abs_sum(other));
	}
	else
	{
		return (this->abs_sub(other));
	}
}

BinInt   BinInt::operator-(const BinInt& other) const
{
	if (this->_sign != other._sign)
	{
		return (this->abs_sum(other));
	}
	else
	{
		return (this->abs_sub(other));
	}
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
	if (other._len > this->_capacity)
	{
		this->extend((other._len * 3) / 2 + 1, false);
		this->_len = other._len;
		this->copy(other);

	}
	else
	{
		this->_len = other._len;
		this->copy(other);
		for (u32 i = this->_len; i < this->_capacity; i++)
			this->_num[i] = 0;
	}
	this->_sign = other._sign;
	return this->normalize();
}

BinInt& BinInt::operator*=(const BinInt& other)
{
	*this = *this * other;
	return *this;
	// TODO: вставьте здесь оператор return
}

BinInt& BinInt::operator+=(const BinInt& other)
{
	*this = *this + other;
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
	BinInt result(*this);
	result._sign = !result._sign;
	return result;
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


