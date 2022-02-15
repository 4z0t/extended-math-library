
#include "Ubit.h"
#define max(a,b) ((a) > (b) ? (a) : (b))
#include <iostream>
using namespace std;
char num_len(uint32_t num)
{
	char i = 0;
	while (num) {
		num >>= 1; i++;
	}
	return i;
}

sum smart_sum(const uint32_t& n1, const uint32_t& n2)
{
	sum result;
	result.num = n1 + n2;
	result.rest = (result.num < max(n1, n2)) ? 1 : 0;
	/*if (result.num < max(n1, n2))
		result.rest = 1;
	else
		result.rest = 0;*/
	return result;
}
//sum smart_sum(const uint32_t& n1, const uint32_t& n2)
//{
//	uint32_t  ac, bc, a, b;
//	sum result;
//	result.rest = 0;
//	a = n1;
//	ac = a & last_bit;
//	a &= mask_last_bit;
//	b = n2;
//	bc = b & last_bit;
//	b &= mask_last_bit;
//	result.num = a + b;
//	if (ac && bc)
//	{
//		result.rest = 1;
//	}
//	else
//	{
//		result.rest = (ac + bc) && (result.num & last_bit);
//		if (result.rest)
//		{
//			result.num &= mask_last_bit;
//		}
//		else
//		{
//			result.num += ac + bc;
//		}
//	}
//	return result;
//}

Ubit Ubit::operator <<(const uint32_t& length) const
{
	if (!length)
		return *this;
	uint32_t cellshift = length / 32;
	char shift = length % 32;
	if (!shift)return this->movecells(cellshift);
	Ubit result(this->get_len() + cellshift + (shift != 0), this->get_sign());
	uint32_t rest = 0;
	for (uint32_t i = 0; i < this->get_len(); i++)
	{
		result.num[i + cellshift] = (this->num[i] << shift) | rest;
		rest = this->num[i] >> (32 - shift);
	}
	if (rest)
		result.num[result.get_len() - 1] = rest;
	return result.antidrain();
}

Ubit Ubit::movecells(const uint32_t& length)const
{
	if (length)
	{
		Ubit result(this->get_len() + length, this->get_sign());
		for (uint32_t i = 0; i < this->get_len(); i++)
			result.num[i + length] = this->num[i];
		return result;
	}
	return *this;
}

Ubit& Ubit::antidrain()
{
	if (this->num[this->get_len() - 1] == 0)
		for (uint32_t i = this->get_len() - 1; ; i--)
			if (this->num[i] != 0 || i == 0)
			{
				this->len_sign = ((i + 1) << 1) + this->get_sign();
				return *this;
			}
	return *this;
}

inline uint32_t Ubit::get_len() const
{
	return this->len_sign >> 1;
}

void Ubit::set_sign(bool sign)
{
	this->len_sign &= len_mask;
	this->len_sign += sign;
}

int64_t Ubit::distance(const Ubit& other) const
{
	return ((int64_t)(this->get_len()) - other.get_len()) * 32 + num_len(this->num[this->get_len() - 1]) - num_len(other.num[other.get_len() - 1]);
}

Ubit Ubit::cut(const uint32_t& length) const
{
	if (this->get_len() > length)
	{
		Ubit result(this->get_len() - length, this->get_sign());
		for (uint32_t i = 0; i < result.get_len(); i++)
		{
			result.num[i] = this->num[i + length];
		}
		return result;
	}
	return 0;
}

Ubit& Ubit::cutthis(const uint32_t& length)
{
	if (this->get_len() > length)
	{
		uint32_t* new_num = new uint32_t[this->len_sign -= (length << 1)]{};
		for (uint32_t i = 0; i < this->get_len(); i++)
		{
			new_num[i] = this->num[i + length];
		}
		delete[] this->num;
		this->num = new_num;
		return *this;
	}
	delete[] this->num;
	this->num = new uint32_t[this->len_sign = 1 << 1]{};
	return *this;
}

inline bool Ubit::get_sign()const
{
	return this->len_sign & 1;
}

Ubit::Ubit(const uint32_t& len, bool negative)
{
	this->num = new uint32_t[len]{};
	this->len_sign = (len << 1) + negative;
}

Ubit& Ubit::movethiscells(const uint32_t& length)
{
	if (!length)return *this;
	uint32_t* new_num = new  uint32_t[this->get_len() + length]{};
	for (uint32_t i = 0; i < this->get_len(); i++)
	{
		new_num[i + length] = this->num[i];
	}
	delete[] this->num;
	this->len_sign += length << 1;
	this->num = new_num;
	return *this;
}

Ubit& Ubit::operator <<=(const uint32_t& length)
{
	if (!length)return *this;
	uint32_t cellshift = length / 32;
	uint8_t shift = length % 32;
	if (!shift)return this->movethiscells(cellshift);
	uint32_t* new_num = new  uint32_t[(uint64_t)this->get_len() + cellshift + (shift != 0)]{};
	uint32_t rest = 0;
	for (uint32_t i = 0; i < this->get_len(); i++)
	{
		new_num[i + cellshift] = (this->num[i] << shift) | rest;
		rest = this->num[i] >> (32 - shift);
	}
	this->len_sign += (cellshift + (shift != 0)) << 1;
	if (rest)
		new_num[this->get_len() - 1] = rest;
	delete[] this->num;
	this->num = new_num;
	return this->antidrain();
}

Ubit Ubit::operator|(const Ubit& other) const
{

	if (this->get_len() >= other.get_len())
	{
		Ubit result = *this;
		result.len_sign &= len_mask | other.get_sign();
		for (uint32_t i = 0; i < other.get_len(); i++)
		{
			result.num[i] |= other.num[i];
		}
		return result;
	}
	else
	{
		Ubit result = other;
		result.len_sign &= len_mask | this->get_sign();
		for (uint32_t i = 0; i < this->get_len(); i++)
		{
			result.num[i] |= this->num[i];
		}
		return result;
	}
}

Ubit Ubit::operator&(const Ubit& other) const
{
	if (this->get_len() >= other.get_len())
	{
		Ubit result(other.get_len(), this->get_sign() && other.get_sign());
		for (uint32_t i = 0; i < other.get_len(); i++)
		{
			result.num[i] = this->num[i] & other.num[i];
		}
		return result.antidrain();
	}
	else
	{
		Ubit result(this->get_len(), this->get_sign() && other.get_sign());
		for (uint32_t i = 0; i < this->get_len(); i++)
		{
			result.num[i] = this->num[i] & other.num[i];
		}
		return result.antidrain();
	}
}

Ubit Ubit::operator^(const Ubit& other) const
{
	if (this->get_len() >= other.get_len())
	{
		Ubit result = *this;
		result.len_sign &= len_mask | other.get_sign();
		for (uint32_t i = 0; i < other.get_len(); i++)
		{
			result.num[i] ^= other.num[i];
		}
		return result.antidrain();
	}
	else
	{
		Ubit result = other;
		result.len_sign &= len_mask | this->get_sign();
		for (uint32_t i = 0; i < this->get_len(); i++)
		{
			result.num[i] ^= this->num[i];
		}
		return result.antidrain();
	}
}

bool Ubit::abs_compare(const Ubit& other)const
{
	if (this->get_len() > other.get_len())
		return true;
	if (this->get_len() < other.get_len())
		return false;
	for (uint32_t i = this->get_len() - 1; ; i--)
	{
		if (this->num[i] != other.num[i])
			return  this->num[i] > other.num[i];
		if (i == 0)
			return false;//equal
	}
}

Ubit::Ubit()
{
	this->len_sign = 0;
	this->num = nullptr;
}

Ubit::~Ubit()
{
	if (this->num != nullptr)delete[] this->num;
}

Ubit::Ubit(const Ubit& other)
{
	this->len_sign = other.len_sign;
	this->num = new uint32_t[this->get_len()]{};
	for (uint32_t i = 0; i < this->get_len(); i++)
		this->num[i] = other.num[i];
	this->antidrain();
}

Ubit::Ubit(const int8_t& value)
{
	this->len_sign = (1 << 1) + (value < 0);
	this->num = new uint32_t[1]{};
	this->num[0] = value * (this->get_sign() ? -1 : 1);
}

Ubit::Ubit(const uint8_t& value)
{
	this->len_sign = 1 << 1;
	this->num = new uint32_t[1]{};
	this->num[0] = value;
}


Ubit::Ubit(const int16_t& value)
{
	this->len_sign = (1 << 1) + (value < 0);
	this->num = new uint32_t[1]{};
	this->num[0] = value * (this->get_sign() ? -1 : 1);
}

Ubit::Ubit(const uint16_t& value)
{
	this->len_sign = 1 << 1;
	this->num = new uint32_t[1]{};
	this->num[0] = value;
}

Ubit::Ubit(const int32_t& value)
{
	this->len_sign = (1 << 1) + (value < 0);
	this->num = new uint32_t[1]{};
	this->num[0] = value * (this->get_sign() ? -1 : 1);
}

Ubit::Ubit(const uint32_t& value)
{
	this->len_sign = 1 << 1;
	this->num = new uint32_t[1]{};
	this->num[0] = value;
}

Ubit::operator bool() const
{
	return !this->zero();
}

Ubit Ubit::operator*(const Ubit& other) const
{
	Ubit result(1u + this->get_len() + other.get_len(), this->get_sign() ^ other.get_sign());
	uint64_t  b;
	sum s; uint32_t rest;
	uint32_t ilen = this->get_len(), jlen = other.get_len();
	for (uint32_t i = 0; i < ilen; i++)
		for (uint32_t j = 0; j < jlen; j++)
		{
			if (this->num[i] && other.num[j])
			{
				b = (uint64_t)this->num[i] * other.num[j];
				s = smart_sum(result.num[i + j], (uint32_t)b);
				result.num[i + j] = s.num;
				rest = s.rest;
				s = smart_sum(result.num[i + j + 1], (b >> 32));
				result.num[i + j + 1] = s.num + rest;
				//if (s.num == mask)cout << "!" << endl;
				if (s.rest)result.num[i + j + 2]++;
			}
		}
	return result.antidrain();
}

Ubit Ubit::operator+(const Ubit& other) const
{
	if (this->get_sign() == other.get_sign())
	{
		if (this->get_len() >= other.get_len())
		{
			Ubit result(1u + this->get_len(), this->get_sign());
			uint32_t rest = 0;
			for (uint32_t i = 0; i < this->get_len(); i++)
			{
				if (i < other.get_len())
				{
					sum s = smart_sum(this->num[i], other.num[i]);
					if (s.num == mask && rest)
					{
						result.num[i] = 0;
						rest = 1;
						continue;
					}
					result.num[i] = rest + s.num;
					//if(s.num==mask)cout <<"!"<< endl;
					rest = s.rest;
					continue;
				}
				else
				{
					if (this->num[i] == mask && rest)
					{
						result.num[i] = 0;
						rest = 1;
						continue;
					}
					result.num[i] = this->num[i] + rest;
				}
				rest = 0;
			}
			result.num[this->get_len()] = rest;
			return result.antidrain();
		}
		else
		{
			return other + *this;
		}
	}
	else
	{
		if (this->abs_compare(other))
		{
			Ubit result = *this;
			for (uint32_t i = 0; i < other.get_len(); i++)
				if (result.num[i] >= other.num[i])
				{
					result.num[i] -= other.num[i];
				}
				else
				{
					uint32_t j = i + 1;
					while (result.num[j] == 0)
					{
						result.num[j++] = mask;
						if (j == result.get_len())
							break;
					}
					result.num[j] -= 1;
					result.num[i] += (~other.num[i]) + 1;
				}
			return result.antidrain();
		}
		else
		{
			Ubit result = other;
			for (uint32_t i = 0; i < this->get_len(); i++)
				if (result.num[i] >= this->num[i])
				{
					result.num[i] -= this->num[i];
				}
				else
				{
					uint32_t j = i + 1;
					while (result.num[j] == 0)
					{
						result.num[j++] = mask;
						if (j == result.get_len())
							break;
					}
					result.num[j] -= 1;
					result.num[i] += (~this->num[i]) + 1;
				}
			return result.antidrain();
		}
	}
}

Ubit Ubit::operator-(const Ubit& other) const
{
	if (this->get_sign() != other.get_sign())
	{
		if (this->get_len() >= other.get_len())
		{
			Ubit result(1u + this->get_len(), this->get_sign());
			uint32_t rest = 0;
			for (uint32_t i = 0; i < this->get_len(); i++)
			{
				if (i < other.get_len())
				{
					sum s = smart_sum(this->num[i], other.num[i]);
					if (s.num == mask && rest)
					{
						result.num[i] = 0;
						rest = 1;
						continue;
					}
					result.num[i] = rest + s.num;
					rest = s.rest;
					continue;
				}
				else
				{
					if (this->num[i] == mask && rest)
					{
						result.num[i] = 0;
						rest = 1;
						continue;
					}
					result.num[i] = this->num[i] + rest;
				}
				rest = 0;
			}
			result.num[this->get_len()] = rest;
			return result.antidrain();
		}
		else
		{
			return other + *this;
		}
	}
	else
	{
		if (this->abs_compare(other))
		{
			Ubit result = *this;
			for (uint32_t i = 0; i < other.get_len(); i++)
				if (result.num[i] >= other.num[i])
				{
					result.num[i] -= other.num[i];
				}
				else
				{
					uint32_t j = i + 1;
					while (result.num[j] == 0)
					{
						result.num[j++] = mask;
						if (j == result.get_len())
							break;
					}
					result.num[j] -= 1;
					result.num[i] += (~other.num[i]) + 1;
				}
			return result.antidrain();
		}
		else
		{
			Ubit result = -other;
			for (uint32_t i = 0; i < this->get_len(); i++)
				if (result.num[i] >= this->num[i])
				{
					result.num[i] -= this->num[i];
				}
				else
				{
					uint32_t j = i + 1;
					while (result.num[j] == 0)
					{
						result.num[j++] = mask;
						if (j == result.get_len())
							break;
					}
					result.num[j] -= 1;
					result.num[i] += (~this->num[i]) + 1;
				}
			return result.antidrain();
		}
	}
}

Ubit Ubit::operator/(const Ubit& other) const
{
	if (other.zero())
		exit(ZERO_DIVISION_ERROR_CODE);
	Ubit numerator = *this;
	numerator.len_sign &= len_mask;
	Ubit result = 0;
	Ubit divider = other;
	divider.len_sign &= len_mask;
	Ubit step = 1;
	while (true)
	{
		if (divider > numerator)
			break;
		int64_t counter = numerator.distance(divider) - 1;
		while (numerator >= (divider << (++counter)));
		numerator -= (divider << (counter - 1));
		result += (step << (counter - 1));
		/*divider <<= (counter - 1);
		step <<= (counter - 1);
		numerator -= divider;
		result += step;*/
	}
	/*if (result * other + numerator != *this)
	{
		result.convert().print();
		numerator.convert().print();
		other.convert().print();
		this->convert().print();
		(this->convert() / other.convert()).print();
		(this->convert() % other.convert()).print();
		(result.convert() * other.convert()).print();
		this->print();
		(result * other).print();
		numerator.print();
		(result * other + numerator).print();

	}*/

	result.len_sign &= (this->get_sign() ^ other.get_sign()) + len_mask;
	return result.antidrain();
}


Ubit Ubit::operator%(const Ubit& other) const
{
	if (other.zero())
		exit(ZERO_DIVISION_ERROR_CODE);
	Ubit numerator = *this;
	numerator.len_sign &= len_mask;
	Ubit divider = other;
	divider.len_sign &= len_mask;
	while (true)
	{
		if (divider > numerator)
			break;
		int64_t counter = numerator.distance(divider) - 1;
		while (numerator >= (divider << (++counter)));
		numerator -= (divider << (counter - 1));
	}
	//numerator.len_sign &= (this->get_sign() ^ other.get_sign()) + len_mask;
	return numerator.antidrain();
}

Ubit& Ubit::operator=(const Ubit& other)
{
	if (this->num != nullptr)delete[]this->num;
	this->len_sign = other.len_sign;
	this->num = new uint32_t[this->get_len()]{};
	for (uint32_t i = 0; i < this->get_len(); i++)
		this->num[i] = other.num[i];
	return this->antidrain();
}

Ubit& Ubit::operator*=(const Ubit& other)
{
	return *this = *this * other;
}

Ubit& Ubit::operator+=(const Ubit& other)
{
	return *this = *this + other;
}

Ubit& Ubit::operator-=(const Ubit& other)
{
	return *this = *this - other;
}

Ubit& Ubit::operator%=(const Ubit& other)
{
	return *this = *this % other;
}

Ubit& Ubit::operator/=(const Ubit& other)
{
	return *this = *this / other;
}

Ubit Ubit::operator-() const
{
	Ubit result = *this;
	if (result.get_sign())
		result.len_sign--;
	else
		result.len_sign++;
	return result;
}


Ubit::Ubit(const uint64_t& value)
{
	if ((value >> 32) == 0)
	{
		*this = uint32_t(value);
	}
	else
	{
		this->len_sign = (2 << 1);
		this->num = new uint32_t[2]{};
		this->num[0] = (uint32_t)value;
		this->num[1] = value >> 32;
	}
}

bool  Ubit::operator==(const Ubit& other)const
{
	if (this->get_sign() != other.get_sign())
		return false;
	if (this->get_len() != other.get_len())
		return false;
	for (uint32_t i = other.get_len() - 1;; i--)
	{
		if (this->num[i] != other.num[i])
			return  false;
		if (i == 0)
			return true;
	}
}

bool  Ubit::operator!=(const Ubit& other)const
{
	return !(*this == other);
}

bool Ubit::operator>(const Ubit& other)const
{
	if (!this->get_sign() && other.get_sign())
		return true;
	if (this->get_sign() && !other.get_sign())
		return false;
	return (!(this->get_sign() && other.get_sign())) == (this->abs_compare(other));
}

bool Ubit::operator>=(const Ubit& other)const
{
	if (!this->get_sign() && other.get_sign())
		return true;
	if (this->get_sign() && !other.get_sign())
		return false;
	if (*this == other)
		return true;
	return ((!(this->get_sign() && other.get_sign())) == (this->abs_compare(other)));
}

bool Ubit::operator<(const Ubit& other)const
{
	if (this->get_sign() && !other.get_sign())
		return true;
	if (!this->get_sign() && other.get_sign())
		return false;
	return (!(this->get_sign() && other.get_sign())) == (other.abs_compare(*this));
}

bool Ubit::operator<=(const Ubit& other)const
{
	if (this->get_sign() && !other.get_sign())
		return true;
	if (!this->get_sign() && other.get_sign())
		return false;
	if (*this == other)
		return true;
	return (!(this->get_sign() && other.get_sign())) == (other.abs_compare(*this));
}

bool Ubit::zero()const
{
	return this->num[this->get_len() - 1] == 0;
}

Ubit abs(const Ubit& value)
{
	Ubit result = value;
	result.len_sign &= len_mask;
	return result;
}

Ubit gcd(const Ubit& value1, const Ubit& value2)
{
	Ubit n1 = abs(value1);
	Ubit n2 = abs(value2);
	while (n1 != n2)
	{
		if (n1.zero())
			return  n2;
		if (n2.zero())
			return n1;
		if (n1 > n2)
			n1 %= n2;
		//n1 = n1 % n2;
		else
			n2 %= n1;
		//n2 = n2 % n1;
		
	}
	return n1;
}

Ubit pow(const Ubit& other, const uint32_t& n)
{
	Ubit result = 1;
	Ubit buffer = other;
	for (uint8_t i = 0; i < sizeof(n) * 8 && (1 << i) <= n; i++)
	{
		//std::cout << i << std::endl;
		if (n & (1 << i))
			result *= buffer;
		if ((1 << i) < n)
			buffer *= buffer;
	}
	return result;
}

Ubit Ubit::operator++(int)
{
	Ubit copy(*this);
	//TODO:
	//optimize it
	*this += 1;
	return copy;
}

Ubit& Ubit::operator++()
{
	
	return (*this += 1);
}