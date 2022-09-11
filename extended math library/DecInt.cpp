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
		return result.cut_zeros();
	}
	else
	{
		DecInt result(other._len + 1, this->_sign);
		for (uint32_t i = 0; i < other._len; i++)
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

	DecInt result(this->_len + other._len + 1, this->_sign != other._sign);
	for (uint32_t i = 0; i < this->_len; i++)
		for (uint32_t j = 0; j < other._len; j++)
		{
			if (this->_num[i] && other._num[j])
			{
				unsigned long long res = (unsigned long long)this->_num[i] * (unsigned long long)other._num[j];
				result._num[i + j] += res % milrd;
				result._num[i + j + 1] += res / milrd + result._num[i + j] / milrd;
				//result.num[i + j + 2] += result.num[i + j + 1] / milrd;
				//result.num[i + j + 1] %= milrd;
				result._num[i + j] %= milrd;
			}
		}
	return result.cut_zeros();
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
	assert(other.zero());
		
	
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
	return result.cut_zeros();
}

DecInt DecInt::operator%(const DecInt& other) const
{
	return DecInt();
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
		for (uint32_t i = this->_len; i < this->_capacity; i++)
			this->_num[i] = 0;
	}
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
	DecInt result(*this);
	result._sign = !result._sign;
	return result;
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