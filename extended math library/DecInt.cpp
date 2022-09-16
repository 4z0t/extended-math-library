#include "DecInt.h"

inline int64_t DecInt::distance() const
{
	return ((int64_t)this->_len - 1) * 9 + DecInt::dec_int_length(this->_num[this->_len - 1]);
}

inline int64_t DecInt::distance(const DecInt& other) const
{
	return this->distance() - other.distance();
}


int DecInt::dec_int_length(const u32& num)
{
	u32 a = num;
	int length = 0;
	while (a)
	{
		a /= 10;
		length++;
	}
	return length;
}
DecInt::DecInt(const int8_t& value) :DecInt(int32_t(value))
{
}
DecInt::DecInt(const uint8_t& value) :DecInt(int32_t(value))
{
}
DecInt::DecInt(const int16_t& value) :DecInt(int32_t(value))
{
}
DecInt::DecInt(const uint16_t& value) :DecInt(int32_t(value))
{
}
DecInt::DecInt(const int32_t& value) :DecInt(2, false)
{
	this->_sign = (value < 0);
	if (abs(value) >= milrd)
	{
		this->_num[0] = abs(value) % milrd;
		this->_num[1] = abs(value) / milrd;
	}
	else
	{
		this->_len = 1;
		this->_num[0] = abs(value);
	}
}
DecInt::DecInt(const u32& value) :DecInt(2, false)
{
	if (value >= milrd)
	{
		this->_num[0] = value % milrd;
		this->_num[1] = value / milrd;
	}
	else
	{
		this->_len = 1;
		this->_num[0] = value;
	}
}
DecInt::DecInt(const int64_t& value)
{
}
DecInt::DecInt(const uint64_t& value)
{
}
DecInt  DecInt::abs_sum(const DecInt& other) const
{
	std::div_t n;
	int rem = 0;
	if (this->_len > other._len)
	{
		DecInt result(this->_len + 1, this->_sign);
		for (u32 i = 0; i < this->_len; i++)
			if (i < other._len)
			{
				n = std::div(rem + this->_num[i] + other._num[i], (int)milrd);
				result._num[i] += n.rem;
				rem = n.quot;
			}
			else
			{
				n = std::div(rem + this->_num[i] + result._num[i], (int)milrd);
				result._num[i] = n.rem;
				rem = n.quot;
			}
		result._num[this->_len] = rem;
		result.cut_zeros();
		return (result);
	}
	else
	{
		DecInt result(other._len + 1, this->_sign);
		for (u32 i = 0; i < other._len; i++)
			if (i < this->_len)
			{
				n = std::div(rem + this->_num[i] + other._num[i], (int)milrd);
				result._num[i] += n.rem;
				rem = n.quot;
			}
			else
			{
				n = std::div(rem + other._num[i] + result._num[i], (int)milrd);
				result._num[i] = n.rem;
				rem = n.quot;
			}
		result._num[other._len] = rem;
		result.cut_zeros();
		return (result);
	}
}

DecInt  DecInt::abs_sub(const DecInt& other) const
{
	int compare_result = this->abs_compare(other);
	if (compare_result == GREATER)
	{
		DecInt result(*this);
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
					result._num[j++] = milrd - 1;
					if (j == result._len)
						break;
				}
				result._num[j] -= 1;
				result._num[i] += milrd - other._num[i];
			}
		result.cut_zeros();
		return (result);
	}
	else if (compare_result == LESS)
	{
		DecInt result(other);
		result._sign = !result._sign;
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
					result._num[j++] = milrd - 1;
					if (j == result._len)
						break;
				}
				result._num[j] -= 1;
				result._num[i] += milrd - this->_num[i];
			}
		result.cut_zeros();
		return (result);
	}
#ifdef _DEBUG
	else if (compare_result == EQUAL)
	{
		return DecInt(0);
	}
	else
	{
		throw std::logic_error("Unknown compare code");
	}
#endif // _DEBUG
	return DecInt(0);
}


DecInt  DecInt::operator*(const DecInt& other) const
{
	std::lldiv_t r;
	DecInt result(this->_len + other._len + 1, this->_sign != other._sign);
	for (u32 i = 0; i < this->_len; i++)
		for (u32 j = 0; j < other._len; j++)
		{
			if (this->_num[i] && other._num[j])
			{
				int64_t res = static_cast<uint64_t>(this->_num[i]) * static_cast<uint64_t>(other._num[j]);
				r = std::div(res + result._num[i + j], milrd);
				result._num[i + j] = r.rem;
				result._num[i + j + 1] += r.quot;
			}
		}
	return result.normalize();
}

DecInt  DecInt::operator+(const DecInt& other) const
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

DecInt   DecInt::operator-(const DecInt& other) const
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

DecInt  DecInt::move10(const u32& times) const
{
	const u32 shift = times / 9;
	const u32 offset = times % 9;
	DecInt result(this->_len + shift + 1, this->_sign);
	for (u32 i = 0; i < this->_len; i++)
	{
		result._num[i + shift] += (this->_num[i] % pow10(9 - offset)) * pow10(offset);
		result._num[i + shift + 1] += this->_num[i] / pow10(9 - offset);
	}
	return (result.cut_zeros());
}


DecInt& DecInt::movethis10(const u32& times)
{
	const u32 shift = times / 9;
	const u32 offset = times % 9;
	if (this->_capacity < this->_len + shift + 1)
	{
		u32* new_num = new  u32[this->_len + shift + 1]{};
		this->_capacity = this->_len + shift + 1;
		for (u32 i = 0; i < this->_len; i++)
		{
			new_num[i + shift] += (this->_num[i] % pow10(9 - offset)) * pow10(offset);
			new_num[i + shift + 1] += this->_num[i] / pow10(9 - offset);
		}
		delete[] this->_num;
		this->_len = this->_capacity;
		this->_num = new_num;
	}
	else
	{
		u32 v;
		for (u32 i = this->_len - 1; ; i--)
		{
			v = this->_num[i];
			this->_num[i + shift] = (v % pow10(9 - offset)) * pow10(offset);
			this->_num[i + shift + 1] += v / pow10(9 - offset);
			if (i == 0)break;
		}
		for (u32 i = 0; i < shift; i++)
			this->_num[i] = 0;
		this->_len = this->_capacity;
	}

	return this->cut_zeros();
}


DecInt  DecInt::operator/(const DecInt& other) const
{
	if (other.zero())
	{
		throw std::invalid_argument("Zero division exception");
	}

	DecInt numerator = *this;
	numerator._sign = false;
	DecInt result = 0;
	DecInt divider;
	DecInt step;
	while (true)
	{
		divider = other;
		divider._sign = false;
		step = 1;
		if (divider > numerator)
			break;
		int64_t counter = numerator.distance(divider) - 1;
		while (numerator >= divider.move10(++counter));

		divider.movethis10(counter - 1);
		step.movethis10(counter - 1);

		while (numerator >= divider)
		{
			numerator -= divider;
			result += step;
		}
	}
	result._sign = this->_sign != other._sign;
	return (result.normalize());
}

DecInt  DecInt::operator%(const DecInt& other) const
{
	if (other.zero())
	{
		throw std::invalid_argument("Zero division exception");
	}
	DecInt numerator = *this;
	numerator._sign = false;
	DecInt divider;
	while (true)
	{
		divider = other;
		divider._sign = false;
		if (divider > numerator)
			return (numerator.normalize());
		int64_t counter = numerator.distance(divider) - 1;
		while (numerator >= divider.move10(++counter));//FIXIT
		divider.movethis10(counter - 1);
		while (numerator >= divider)
			numerator -= divider;
	}
}

DecInt& DecInt::operator=(const DecInt& other)
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

DecInt& DecInt::operator*=(const DecInt& other)
{
	*this = *this * other;
	return *this;
}

DecInt& DecInt::operator+=(const DecInt& other)
{
	*this = DecInt(*this) + other;
	return *this;
}

DecInt& DecInt::operator-=(const DecInt& other)
{
	*this = *this - other;
	return *this;
}

DecInt& DecInt::operator/=(const DecInt& other)
{
	*this = *this / other;
	return *this;
}

DecInt& DecInt::operator%=(const DecInt& other)
{
	return *this;
}

DecInt& DecInt::operator++()
{
	return *this;
}

DecInt DecInt::operator++(int)
{
	return DecInt();
}

DecInt& DecInt::operator--()
{
	return *this;
}

DecInt DecInt::operator--(int)
{
	return DecInt();
}

DecInt DecInt::operator-() const
{
	DecInt result(*this);
	result._sign = !result._sign;
	return result;
}


//#if _HAS_CXX17
//DecInt& DecInt::operator=(DecInt&& other)
//{
//	if (this->_num != nullptr)
//		delete[]this->_num;
//	this->_capacity = other._capacity;
//	this->_len = other._len;
//	this->_sign = other._sign;
//	this->_num = other._num;
//
//	other._num = nullptr;
//	other._sign = false;
//	other._len = 0;
//	other._capacity = 0;
//	return *this;
//}
//#endif










#ifdef _INITIALIZER_LIST_
DecInt::DecInt(std::initializer_list<u32> num, bool negative)
{

	if (this->_num)delete[]this->_num;
	this->_sign = negative;
	u32  j = (this->_len = num.size());
	this->_capacity = this->_len;
	this->_num = new u32[this->_len]{};
	for (u32 i : num)
	{
#ifdef _DEBUG
		if (i >= milrd)throw std::invalid_argument("Invalid decimal number initialization");
#endif // _DEBUG

		this->_num[--j] = i;
	}
	this->normalize();
}
#endif