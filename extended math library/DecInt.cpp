#include "DecInt.h"

inline int64_t DecInt::distance() const
{
	return ((int64_t)this->_len - 1) * 9 + DecInt::dec_int_length(this->_num[this->_len - 1]);
}

inline int64_t DecInt::distance(const DecInt& other) const
{
	return ((int64_t)this->_len - other._len) * 9 + DecInt::dec_int_length(this->_num[this->_len - 1]) - DecInt::dec_int_length(other._num[other._len - 1]);
}


int DecInt::dec_int_length(const uint32_t& num)
{
	uint32_t a = num;
	int length = 0;
	while (a)
	{
		a /= 10;
		length++;
	}
	return length;
}
DecInt::DecInt(const int8_t& value)
{
}
DecInt::DecInt(const uint8_t& value)
{
}
DecInt::DecInt(const int16_t& value)
{
}
DecInt::DecInt(const uint16_t& value)
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
DecInt::DecInt(const uint32_t& value)
{
}
DecInt::DecInt(const int64_t& value)
{
}
DecInt::DecInt(const uint64_t& value)
{
}
DecInt DecInt::abs_sum(const DecInt& other) const
{
	std::div_t n;
	int rem = 0;
	if (this->_len > other._len)
	{
		DecInt result(this->_len + 1, this->_sign);
		for (uint32_t i = 0; i < this->_len; i++)
			if (i < other._len)
			{
				if (this->_num[i] + other._num[i] == 0)
					continue;
				n = std::div(rem + this->_num[i] + other._num[i], (int)milrd);
				result._num[i] += n.rem;
				rem = n.quot;
			}
			else
			{
				if (this->_num[i] == 0)
					continue;
				n = std::div(rem + this->_num[i] + result._num[i], (int)milrd);
				result._num[i] = n.rem;
				rem = n.quot;
			}
		result._num[this->_len] = rem;
		return result.cut_zeros();
	}
	else
	{
		DecInt result(other._len + 1, this->_sign);
		for (uint32_t i = 0; i < other._len; i++)
			if (i < this->_len)
			{
				if (this->_num[i] + other._num[i] == 0)
					continue;
				n = std::div(rem + this->_num[i] + other._num[i], (int)milrd);
				result._num[i] += n.rem;
				rem = n.quot;
			}
			else
			{
				if (other._num[i] == 0)
					continue;
				n = std::div(rem + other._num[i] + result._num[i], (int)milrd);
				result._num[i] = n.rem;
				rem = n.quot;
			}
		result._num[other._len] = rem;
		return result.cut_zeros();
	}
}

DecInt DecInt::abs_sub(const DecInt& other) const
{
	int compare_result = this->abs_compare(other);
	if (compare_result == GREATER)
	{
		DecInt result(*this);
		for (uint32_t i = 0; i < other._len; i++)
			if (result._num[i] >= other._num[i])
			{
				result._num[i] -= other._num[i];
			}
			else
			{
				uint32_t j = i + 1;
				while (result._num[j] == 0)
				{
					result._num[j++] = milrd - 1;
					if (j == result._len)
						break;
				}
				result._num[j] -= 1;
				result._num[i] += milrd - other._num[i];
			}

		return result.cut_zeros();
	}
	else if (compare_result == LESS)
	{
		DecInt result(other);
		result._sign = !result._sign;
		for (uint32_t i = 0; i < this->_len; i++)
			if (result._num[i] >= this->_num[i])
			{
				result._num[i] -= this->_num[i];
			}
			else
			{
				uint32_t j = i + 1;
				while (result._num[j] == 0)
				{
					result._num[j++] = milrd - 1;
					if (j == result._len)
						break;
				}
				result._num[j] -= 1;
				result._num[i] += milrd - this->_num[i];
			}
		return result.cut_zeros();
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


DecInt DecInt::operator*(const DecInt& other) const
{
	return DecInt();
}

DecInt DecInt::operator+(const DecInt& other) const
{
	if (this->_sign == other._sign)
	{
		return this->abs_sum(other);
	}
	else
	{
		return this->abs_sub(other);
	}
}

DecInt DecInt::operator-(const DecInt& other) const
{
	if (this->_sign != other._sign)
	{
		return this->abs_sum(other);
	}
	else
	{
		return this->abs_sub(other);
	}
}

DecInt DecInt::operator/(const DecInt& other) const
{
	return DecInt();
}

DecInt DecInt::operator%(const DecInt& other) const
{
	return DecInt();
}

DecInt& DecInt::operator=(const DecInt& other)
{
	return *this;
}

DecInt& DecInt::operator*=(const DecInt& other)
{
	return *this;
}

DecInt& DecInt::operator+=(const DecInt& other)
{
	return *this;
}

DecInt& DecInt::operator-=(const DecInt& other)
{
	return *this;
}

DecInt& DecInt::operator/=(const DecInt& other)
{
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
	return DecInt();
}


#ifdef _INITIALIZER_LIST_
DecInt::DecInt(std::initializer_list<uint32_t> num, bool negative)
{

	if (this->_num)delete[]this->_num;
	this->_sign = negative;
	uint32_t  j = (this->_len = num.size());
	this->_capacity = this->_len;
	this->_num = new uint32_t[this->_len]{};
	for (uint32_t i : num)
	{
#ifdef _DEBUG
		if (i >= milrd)throw std::invalid_argument("Invalid decimal number initialization");
#endif // _DEBUG

		this->_num[--j] = i;
	}
	this->cut_zeros();
}
#endif