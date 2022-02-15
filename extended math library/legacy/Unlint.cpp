#include "Unlint.h"


Unlint Unlint::cut(const uint32_t& length)const
{
	if (this->len > length)
	{
		Unlint new_unlint(this->len - length, this->negative);
		for (uint32_t i = 0; i < new_unlint.len; i++)
		{
			new_unlint.num[i] = this->num[i + length];
		}
		return new_unlint;
	}
	return 0;
}

Unlint& Unlint::cutthis(const uint32_t& length)
{
	if (this->len > length)
	{
		uint32_t* new_num = new uint32_t[this->len -= length]{};
		for (uint32_t i = 0; i < this->len; i++)
		{
			new_num[i] = this->num[i + length];
		}
		delete[] this->num;
		this->num = new_num;
		return *this;
	}
	delete[] this->num;
	this->num = new uint32_t[this->len = 1]{};
	return *this;
}

void Unlint::extend()
{
	uint32_t* new_num = new uint32_t[this->len + 1]{};
	for (uint32_t i = 0; i < this->len; i++)
		new_num[i] = this->num[i];
	delete[] this->num;
	this->len++;
	this->num = new_num;
}

int length_int(const uint32_t& num)
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
uint32_t pow10(const int& value)
{
	int result = 1;
	for (int i = 0; i < value; i++)
		result *= 10;
	return result;
}

uint32_t niv(const uint32_t& num, const uint32_t& index)
{
	uint32_t a = num;
	for (uint32_t i = 0; i < index; i++)
		a /= 10;
	return a % 10;
}

bool  Unlint::operator==(const Unlint& other)const
{
	if (this->negative != other.negative)
		return false;
	if (this->len != other.len)
		return false;
	for (uint32_t i = other.len - 1;; i--)
	{
		if (this->num[i] != other.num[i])
			return  false;
		if (i == 0)
			return true;
	}
}

bool  Unlint::operator!=(const Unlint& other)const
{
	return !(*this == other);
}

bool Unlint::operator>(const Unlint& other)const
{
	if (!this->negative && other.negative)
		return true;
	if (this->negative && !other.negative)
		return false;
	return (!(this->negative && other.negative)) == (*this >> other);
}

bool Unlint::operator>=(const Unlint& other)const
{
	if (!this->negative && other.negative)
		return true;
	if (this->negative && !other.negative)
		return false;
	if (*this == other)
		return true;
	return ((!(this->negative && other.negative)) == (*this >> other));
}

bool Unlint::operator<(const Unlint& other)const
{
	if (this->negative && !other.negative)
		return true;
	if (!this->negative && other.negative)
		return false;
	return (!(this->negative && other.negative)) == (*this << other);
}

bool Unlint::operator<=(const Unlint& other)const
{
	if (this->negative && !other.negative)
		return true;
	if (!this->negative && other.negative)
		return false;
	if (*this == other)
		return true;
	return ((!(this->negative && other.negative)) == (*this << other));
}

Unlint::operator bool() const
{
	return !this->zero();
}

Unlint::Unlint(const uint32_t& num_len, bool negative)
{
	this->negative = negative;
	this->len = num_len;
	this->num = new uint32_t[this->len]{};
}

Unlint::Unlint()
{
	this->len = 1;
	this->num = new uint32_t[this->len]{};
}

Unlint& Unlint::operator=(const Unlint& other)
{
	delete[] this->num;
	for (uint32_t i = other.len - 1;; i--)
		if (other.num[i] != 0 || i == 0)
		{
			this->len = i + 1;
			break;
		}
	this->negative = other.negative;
	this->num = new uint32_t[this->len]{};
	for (uint32_t i = 0; i < this->len; i++)
		this->num[i] = other.num[i];
	return *this;
}

Unlint& Unlint::antidrain()
{
	if (this->num[this->len - 1] == 0)
		for (uint32_t i = this->len - 1; ; i--)
			if (this->num[i] != 0 || i == 0)
			{
				this->len = i + 1;
				return *this;
			}
	return *this;
}

Unlint::Unlint(const Unlint& other)
{
	for (uint32_t i = other.len - 1;; i--)
		if (other.num[i] != 0 || i == 0)
		{
			this->len = i + 1;
			break;
		}
	this->negative = other.negative;
	this->num = new uint32_t[this->len]{};
	for (uint32_t i = 0; i < this->len; i++)
		this->num[i] = other.num[i];
}

Unlint::Unlint(const uint8_t& value)
{
	this->num = new uint32_t[this->len = 1]{};
	this->num[0] = value;
}


Unlint::Unlint(const int8_t& value)
{
	this->negative = (value < 0);
	this->num = new uint32_t[this->len = 1]{};
	this->num[0] = abs(value);
}

Unlint::Unlint(const uint16_t& value)
{
	this->num = new uint32_t[this->len = 1]{};
	this->num[0] = value;
}

Unlint::Unlint(const int16_t& value)
{
	this->negative = (value < 0);
	this->num = new uint32_t[this->len = 1]{};
	this->num[0] = abs(value);
}

Unlint::Unlint(const uint32_t* num, const uint32_t& len, bool negative)
{
	for (uint32_t i = len - 1;; i--)
		if (num[len - i - 1] != 0 || i == 0)
		{
			this->len = i + 1;
			break;
		}
	this->negative = negative;
	this->num = new uint32_t[this->len]{};
	for (uint32_t i = 0; i < this->len; i++)
		this->num[i] = num[len - i - 1];
}

Unlint Unlint::ten(const uint32_t& power)
{
	return  Unlint(pow10(power % 9)).movecells(power / 9);
}

Unlint::~Unlint()
{
	if (this->num != nullptr)delete[] this->num;
}

//Unlint Unlint::move10(const uint32_t& times)
//{
//	if (!times)
//		return *this;
//	Unlint new_unlint(this->len + times / 9 + 1, this->negative);
//	for (uint32_t i = 0; i < this->len; i++)
//	{
//		new_unlint.num[i + times / 9] += (this->num[i] % pow10(9 - times % 9)) * pow10(times % 9);
//		new_unlint.num[i + times / 9 + 1] += this->num[i] / pow10(9 - times % 9);
//	}
//	return new_unlint.antidrain();
//}

Unlint Unlint::move10(const uint32_t& times) const
{
	Unlint new_unlint(this->len + times / 9 + 1, this->negative);
	for (uint32_t i = 0; i < this->len; i++)
	{
		new_unlint.num[i + times / 9] += (this->num[i] % pow10(9 - times % 9)) * pow10(times % 9);
		new_unlint.num[i + times / 9 + 1] += this->num[i] / pow10(9 - times % 9);
	}
	return new_unlint.antidrain();
}

Unlint Unlint::movecells(const uint32_t& length)const
{
	if (length)
	{
		Unlint new_unlint(this->len + length, this->negative);
		for (uint32_t i = 0; i < this->len; i++)
			new_unlint.num[i + length] = this->num[i];
		return new_unlint;
	}
	return *this;
}

Unlint& Unlint::movethis10(const uint32_t& times)
{
	uint32_t* new_num = new  uint32_t[this->len + times / 9 + 1]{};
	for (uint32_t i = 0; i < this->len; i++)
	{
		new_num[i + times / 9] += (this->num[i] % pow10(9 - times % 9)) * pow10(times % 9);
		new_num[i + times / 9 + 1] += this->num[i] / pow10(9 - times % 9);
	}
	delete[] this->num;
	this->len += times / 9 + 1;
	this->num = new_num;
	return this->antidrain();
}

Unlint& Unlint::movethiscells(const uint32_t& length)
{
	if (length)
	{
		uint32_t* new_num = new  uint32_t[this->len + length]{};
		for (uint32_t i = 0; i < this->len; i++)
		{
			new_num[i + length] = this->num[i];
		}
		delete[] this->num;
		this->len += length;
		this->num = new_num;
	}
	return *this;
}

Unlint sqr(const Unlint& other)
{
	return other * other;
}

Unlint pow(const Unlint& other, const uint32_t& n)
{
	Unlint result = 1;
	Unlint buffer = other;
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

Unlint sqrt(const Unlint& value)
{
	if (value.negative)
		throw NEGATIVE_ARGUMENT_ERROR_CODE;
		//exit(NEGATIVE_ARGUMENT_ERROR_CODE);
	Unlint prev = 0;
	Unlint res = 1;
	while (prev != res)
	{
		prev = res;
		res = (res + value / res) / 2;
	}
	return res;
}

//Unlint Unlint::operator*(const Unlint& other)
//{
//	Unlint result(this->len + other.len, this->negative != other.negative);
//	for (uint32_t i = 0; i < this->len; i++)
//		for (uint32_t j = 0; j < other.len; j++)
//		{
//			if (this->num[i] && other.num[j])
//			{
//				unsigned long long res = (unsigned long long)this->num[i] * (unsigned long long)other.num[j];
//				result.num[i + j] += res % milrd;
//				result.num[i + j + 1] += res / milrd + result.num[i + j] / milrd;
//				//result.num[i + j + 2] += result.num[i + j + 1] / milrd;
//				//result.num[i + j + 1] %= milrd;
//				result.num[i + j] %= milrd;
//			}
//		}
//	return result.antidrain();
//}

Unlint Unlint::operator*(const Unlint& other) const
{
	Unlint result(this->len + other.len, this->negative != other.negative);
	for (uint32_t i = 0; i < this->len; i++)
		for (uint32_t j = 0; j < other.len; j++)
		{
			if (this->num[i] && other.num[j])
			{
				unsigned long long res = (unsigned long long)this->num[i] * (unsigned long long)other.num[j];
				result.num[i + j] += res % milrd;
				result.num[i + j + 1] += res / milrd + result.num[i + j] / milrd;
				//result.num[i + j + 2] += result.num[i + j + 1] / milrd;
				//result.num[i + j + 1] %= milrd;
				result.num[i + j] %= milrd;
			}
		}
	return result.antidrain();
}

Unlint& Unlint::operator*=(const Unlint& other)
{
	Unlint result(this->len + other.len, this->negative != other.negative);
	for (uint32_t i = 0; i < this->len; i++)
		for (uint32_t j = 0; j < other.len; j++)
		{
			if (this->num[i] && other.num[j])
			{
				unsigned long long res = (unsigned long long)this->num[i] * (unsigned long long)other.num[j];
				result.num[i + j] += res % milrd;
				result.num[i + j + 1] += res / milrd + result.num[i + j] / milrd;
				//result.num[i + j + 2] += result.num[i + j + 1] / milrd;
				//result.num[i + j + 1] %= milrd;
				result.num[i + j] %= milrd;
			}
		}
	return *this = result;
}

Unlint Unlint::operator-(const Unlint& other)const
{
	if (this->negative != other.negative)
	{
		if (this->len > other.len)
		{
			Unlint result(this->len + 1, this->negative);
			for (uint32_t i = 0; i < this->len; i++)
				if (i < other.len)
				{
					if (this->num[i] + other.num[i] == 0)
						continue;
					result.num[i] += (this->num[i] + other.num[i]) % milrd;
					result.num[i + 1] += (this->num[i] + other.num[i]) / milrd;
					result.num[i + 1] += result.num[i] / milrd;
					result.num[i] %= milrd;
				}
				else
				{
					if (this->num[i] == 0)
						continue;
					result.num[i] += this->num[i];
					result.num[i + 1] += result.num[i] / milrd;
					result.num[i] %= milrd;
				}
			return result.antidrain();
		}
		else
		{
			Unlint result(other.len + 1, other.negative);
			for (uint32_t i = 0; i < other.len; i++)
				if (i < this->len)
				{
					if (this->num[i] + other.num[i] == 0) //if(!(this->num[i]+other.num[i])) whats faster?
						continue;
					result.num[i] += (this->num[i] + other.num[i]) % milrd;
					result.num[i + 1] += (this->num[i] + other.num[i]) / milrd;
					result.num[i + 1] += result.num[i] / milrd;
					result.num[i] %= milrd;
				}
				else
				{
					if (other.num[i] == 0)
						continue;
					result.num[i] += other.num[i];
					result.num[i + 1] += result.num[i] / milrd;
					result.num[i] %= milrd;
				}

			return result.antidrain();
		}
	}
	else
	{
		if (*this >> other)
		{
			Unlint result = *this;
			for (uint32_t i = 0; i < other.len; i++)
				if (result.num[i] >= other.num[i])
				{
					result.num[i] -= other.num[i];
				}
				else
				{
					int j = i + 1;
					while (result.num[j] == 0)
					{
						result.num[j++] = milrd - 1;
						if (j == result.len)
							break;
					}
					result.num[j] -= 1;
					result.num[i] += milrd - other.num[i];
				}

			return result.antidrain();
		}
		else
		{
			Unlint result = other;
			result.negative = !result.negative;
			for (uint32_t i = 0; i < this->len; i++)
				if (result.num[i] >= this->num[i])
				{
					result.num[i] -= this->num[i];
				}
				else
				{
					uint32_t j = i + 1;
					while (result.num[j] == 0)
					{
						result.num[j++] = milrd - 1;
						if (j == result.len)
							break;
					}
					result.num[j] -= 1;
					result.num[i] += milrd - this->num[i];
				}

			return result.antidrain();
		}
	}
}



Unlint& Unlint::operator-=(const Unlint& other)
{
	if (this->negative != other.negative)
	{
		if (this->len > other.len)
		{
			Unlint result(this->len + 1, this->negative);
			for (uint32_t i = 0; i < this->len; i++)
				if (i < other.len)
				{
					if (this->num[i] + other.num[i] == 0)
						continue;
					result.num[i] += (this->num[i] + other.num[i]) % milrd;
					result.num[i + 1] += (this->num[i] + other.num[i]) / milrd;
					result.num[i + 1] += result.num[i] / milrd;
					result.num[i] %= milrd;
				}
				else
				{
					if (this->num[i] == 0)
						continue;
					result.num[i] += this->num[i];
					result.num[i + 1] += result.num[i] / milrd;
					result.num[i] %= milrd;
				}
			return *this = result;
		}
		else
		{
			Unlint result(other.len + 1, other.negative);
			for (uint32_t i = 0; i < other.len; i++)
				if (i < this->len)
				{
					if (this->num[i] + other.num[i] == 0) //if(!(this->num[i]+other.num[i])) whats faster?
						continue;
					result.num[i] += (this->num[i] + other.num[i]) % milrd;
					result.num[i + 1] += (this->num[i] + other.num[i]) / milrd;
					result.num[i + 1] += result.num[i] / milrd;
					result.num[i] %= milrd;
				}
				else
				{
					if (other.num[i] == 0)
						continue;
					result.num[i] += other.num[i];
					result.num[i + 1] += result.num[i] / milrd;
					result.num[i] %= milrd;
				}

			return *this = result;
		}
	}
	else
	{
		if (*this >> other)
		{
			Unlint result = *this;
			for (uint32_t i = 0; i < other.len; i++)
				if (result.num[i] >= other.num[i])
				{
					result.num[i] -= other.num[i];
				}
				else
				{
					uint32_t j = i + 1;
					while (result.num[j] == 0)
					{
						result.num[j++] = milrd - 1;
						if (j == result.len)
							break;
					}
					result.num[j] -= 1;
					result.num[i] += milrd - other.num[i];
				}

			return *this = result;
		}
		else
		{
			Unlint result = other;
			result.negative = !result.negative;
			for (uint32_t i = 0; i < this->len; i++)
				if (result.num[i] >= this->num[i])
				{
					result.num[i] -= this->num[i];
				}
				else
				{
					uint32_t j = i + 1;
					while (result.num[j] == 0)
					{
						result.num[j++] = milrd - 1;
						if (j == result.len)
							break;
					}
					result.num[j] -= 1;
					result.num[i] += milrd - this->num[i];
				}

			return *this = result;
		}
	}
}

Unlint& Unlint::operator/=(const Unlint& other)
{
	if (other.zero())
		exit(ZERO_DIVISION_ERROR_CODE);
	bool numsign = this->negative != other.negative;
	this->negative = false;
	Unlint result = 0;
	while (true)
	{
		Unlint divider = other;
		divider.negative = false;
		Unlint step = 1;
		if (divider > *this)
			break;

		int64_t counter = this->distance(divider) - 1;
		while (*this >= divider.move10(++counter));

		divider.movethis10(counter - 1);
		step.movethis10(counter - 1);

		while (*this >= divider)
		{
			*this -= divider;
			result += step;
		}
	}
	*this = result;
	this->negative = numsign;
	return *this;

}

Unlint Unlint::operator+(const Unlint& other)const
{
	if (this->negative == other.negative)
	{
		Unlint result(1 + ((this->len > other.len) ? this->len : other.len), this->negative);
		if (this->len > other.len)
		{
			for (uint32_t i = 0; i < this->len; i++)
				if (i < other.len)
				{
					if (this->num[i] + other.num[i] == 0)
						continue;
					result.num[i] += (this->num[i] + other.num[i]) % milrd;
					result.num[i + 1] += (this->num[i] + other.num[i]) / milrd;
					result.num[i + 1] += result.num[i] / milrd;
					result.num[i] %= milrd;
				}
				else
				{
					if (this->num[i] == 0)
						continue;
					result.num[i] += this->num[i];
					result.num[i + 1] += result.num[i] / milrd;
					result.num[i] %= milrd;
				}
		}
		else
		{
			for (uint32_t i = 0; i < other.len; i++)
				if (i < this->len)
				{
					if (this->num[i] + other.num[i] == 0)
						continue;
					result.num[i] += (this->num[i] + other.num[i]) % milrd;
					result.num[i + 1] += (this->num[i] + other.num[i]) / milrd;
					result.num[i + 1] += result.num[i] / milrd;
					result.num[i] %= milrd;
				}
				else
				{
					if (other.num[i] == 0)
						continue;
					result.num[i] += other.num[i];
					result.num[i + 1] += result.num[i] / milrd;
					result.num[i] %= milrd;
				}
		}
		return result.antidrain();
	}
	else
	{
		if (*this >> other)
		{
			Unlint result = *this;
			for (uint32_t i = 0; i < other.len; i++)
				if (result.num[i] >= other.num[i])
				{
					result.num[i] -= other.num[i];
				}
				else
				{
					uint32_t j = i + 1;
					while (result.num[j] == 0)
					{
						result.num[j++] = milrd - 1;
						if (j == result.len)
							break;
					}
					result.num[j] -= 1;
					result.num[i] += milrd - other.num[i];
				}

			return result.antidrain();
		}
		else
		{
			Unlint result = other;
			for (uint32_t i = 0; i < this->len; i++)
				if (result.num[i] >= this->num[i])
				{
					result.num[i] -= this->num[i];
				}
				else
				{
					uint32_t j = i + 1;
					while (result.num[j] == 0)
					{
						result.num[j++] = milrd - 1;
						if (j == result.len)
							break;
					}
					result.num[j] -= 1;
					result.num[i] += milrd - this->num[i];
				}
			return result.antidrain();
		}
	}
}



Unlint& Unlint::operator+=(const Unlint& other)
{
	{
		if (this->negative == other.negative)
		{
			Unlint result(1 + ((this->len > other.len) ? this->len : other.len), this->negative);
			if (this->len > other.len)
			{
				for (uint32_t i = 0; i < this->len; i++)
					if (i < other.len)
					{
						if (this->num[i] + other.num[i] == 0)
							continue;
						result.num[i] += (this->num[i] + other.num[i]) % milrd;
						result.num[i + 1] += (this->num[i] + other.num[i]) / milrd;
						result.num[i + 1] += result.num[i] / milrd;
						result.num[i] %= milrd;
					}
					else
					{
						if (this->num[i] == 0)
							continue;
						result.num[i] += this->num[i];
						result.num[i + 1] += result.num[i] / milrd;
						result.num[i] %= milrd;
					}
			}
			else
			{
				for (uint32_t i = 0; i < other.len; i++)
					if (i < this->len)
					{
						if (this->num[i] + other.num[i] == 0)
							continue;
						result.num[i] += (this->num[i] + other.num[i]) % milrd;
						result.num[i + 1] += (this->num[i] + other.num[i]) / milrd;
						result.num[i + 1] += result.num[i] / milrd;
						result.num[i] %= milrd;
					}
					else
					{
						if (other.num[i] == 0)
							continue;
						result.num[i] += other.num[i];
						result.num[i + 1] += result.num[i] / milrd;
						result.num[i] %= milrd;
					}
			}

			return *this = result;
		}
		else
		{
			if (*this >> other)
			{
				Unlint result = *this;
				for (uint32_t i = 0; i < other.len; i++)
					if (result.num[i] >= other.num[i])
					{
						result.num[i] -= other.num[i];
					}
					else
					{
						uint32_t j = i + 1;
						while (result.num[j] == 0)
						{
							result.num[j++] = milrd - 1;
							if (j == result.len)
								break;
						}
						result.num[j] -= 1;
						result.num[i] += milrd - other.num[i];
					}

				return *this = result;
			}
			else
			{
				Unlint result = other;
				for (uint32_t i = 0; i < this->len; i++)
					if (result.num[i] >= this->num[i])
					{
						result.num[i] -= this->num[i];
					}
					else
					{
						uint32_t j = i + 1;
						while (result.num[j] == 0)
						{
							result.num[j++] = milrd - 1;
							if (j == result.len)
								break;
						}
						result.num[j] -= 1;
						result.num[i] += milrd - this->num[i];
					}
				return *this = result;
			}
		}
	}
}

bool  Unlint::operator>>(const Unlint& other)const
{
	if (this->len > other.len)
		return true;
	if (this->len < other.len)
		return false;
	for (uint32_t i = this->len - 1; ; i--)
	{
		if (this->num[i] != other.num[i])
			return  this->num[i] > other.num[i];
		if (i == 0)
			return false;//equal
	}
}

bool  Unlint::operator<<(const Unlint& other)const
{
	if (this->len > other.len)
		return false;
	if (this->len < other.len)
		return true;
	for (uint32_t i = this->len - 1; ; i--)
	{
		if (this->num[i] != other.num[i])
			return  this->num[i] < other.num[i];
		if (i == 0)
			return false;	//equal
	}
}

//bool Unlint::zero()
//{
//	return this->num[this->len - 1] == 0;
//}

bool Unlint::zero()const
{
	return this->num[this->len - 1] == 0;
}

Unlint& Unlint::operator++()
{
	if (this->zero())
	{
		this->num[0] = 1;
		this->negative = false;
		return *this;
	}
	if (this->negative)
	{
		uint32_t j = 0;
		while (this->num[j] == 0)
			this->num[j++] = milrd - 1;
		this->num[j]--;
	}
	else
	{
		uint32_t j = 0;
		while (this->num[j] == milrd - 1)
		{
			this->num[j++] = 0;
			if (j == this->len)
			{
				this->extend();
				break;
			}
		}
		this->num[j]++;
	}
	return this->antidrain();
}


Unlint Unlint::operator++(int)
{
	Unlint result = *this;
	if (this->zero())
	{
		this->num[0] = 1;
		this->negative = false;
	}
	else
	{
		if (this->negative)
		{
			uint32_t j = 0;
			while (this->num[j] == 0)
				this->num[j++] = milrd - 1;
			this->num[j]--;
		}
		else
		{
			uint32_t j = 0;
			while (this->num[j] == milrd - 1)
			{
				this->num[j++] = 0;
				if (j == this->len)
				{
					this->extend();
					break;
				}
			}
			this->num[j]++;
		}
	}
	this->antidrain();//must return prev
	return result;
}

Unlint& Unlint::operator--()
{
	if (this->zero())
	{
		this->num[0] = 1;
		this->negative = true;
		return *this;
	}
	if (this->negative)
	{
		uint32_t j = 0;
		while (this->num[j] == milrd - 1)
		{
			this->num[j++] = 0;
			if (j == this->len)
			{
				this->extend();
				break;
			}
		}
		this->num[j]++;
	}
	else
	{
		uint32_t j = 0;
		while (this->num[j] == 0)
			this->num[j++] = milrd - 1;
		this->num[j]--;
	}
	return this->antidrain();
}

Unlint Unlint::operator--(int)
{
	Unlint result = *this;
	if (this->zero())
	{
		this->num[0] = 1;
		this->negative = true;
	}
	else
	{
		if (this->negative)
		{
			uint32_t j = 0;
			while (this->num[j] == milrd - 1)
			{
				this->num[j++] = 0;
				if (j == this->len)
				{
					this->extend();
					break;
				}
			}
			this->num[j]++;
		}
		else
		{
			uint32_t j = 0;
			while (this->num[j] == 0)
				this->num[j++] = milrd - 1;
			this->num[j]--;
		}
	}
	this->antidrain();//must return prev
	return result;
}

Unlint::Unlint(const int32_t& value)
{
	this->negative = (value < 0);
	if (abs(value) >= milrd)
	{
		this->num = new uint32_t[this->len = 2]{};
		this->num[0] = abs(value) % milrd;
		this->num[1] = abs(value) / milrd;
	}
	else
	{
		this->num = new uint32_t[this->len = 1]{};
		this->num[0] = abs(value);
	}
}

Unlint::Unlint(const uint32_t& value)
{
	this->negative = false;
	if (value >= milrd)
	{
		this->num = new uint32_t[this->len = 2]{};
		this->num[0] = value % milrd;
		this->num[1] = value / milrd;
	}
	else
	{
		this->num = new uint32_t[this->len = 1]{};
		this->num[0] = value;
	}
}

Unlint::Unlint(const int64_t& value)
{
	this->negative = (value < 0);
	if (abs(value) >= 1'000'000'000'000'000'000ll)
	{
		this->num = new uint32_t[this->len = 3]{};
		this->num[0] = abs(value) % milrd;
		this->num[1] = abs(value) / milrd % milrd;
		this->num[2] = abs(value) / 1'000'000'000'000'000'000ll;
	}
	else if (abs(value) >= milrd)
	{
		this->num = new uint32_t[this->len = 2]{};
		this->num[0] = abs(value) % milrd;
		this->num[1] = abs(value) / milrd;
	}
	else
	{
		this->num = new uint32_t[this->len = 1]{};
		this->num[0] = abs(value);
	}
}

Unlint::Unlint(const uint64_t& value)
{
	this->negative = false;
	if (value >= 1'000'000'000'000'000'000ull)
	{
		this->num = new uint32_t[this->len = 3]{};
		this->num[0] = value % milrd;
		this->num[1] = value / milrd % milrd;
		this->num[2] = value / 1'000'000'000'000'000'000ull;
	}
	else if (value >= milrd)
	{
		this->num = new uint32_t[this->len = 2]{};
		this->num[0] = value % milrd;
		this->num[1] = value / milrd;
	}
	else
	{
		this->num = new uint32_t[this->len = 1]{};
		this->num[0] = value;
	}
}

int64_t Unlint::distance(const Unlint& other)const
{
	return ((long long)this->len - other.len) * 9 + length_int(this->num[this->len - 1]) - length_int(other.num[other.len - 1]);
}

int64_t Unlint::distance() const
{
	return ((long long)this->len - 1) * 9 + length_int(this->num[this->len - 1]);
}



Unlint Unlint::operator/(const Unlint& other)const
{
	if (other.zero())
		throw ZERO_DIVISION_ERROR_CODE;
		//exit(ZERO_DIVISION_ERROR_CODE);
	Unlint numerator = *this;
	numerator.negative = false;
	Unlint result = 0;
	while (true)
	{
		Unlint divider = other;
		divider.negative = false;
		Unlint step = 1;
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
	result.negative = this->negative != other.negative;
	return result.antidrain();
}

Unlint Unlint::operator%(const Unlint& other)const
{
	if (other.zero())
		throw ZERO_DIVISION_ERROR_CODE;
		//exit(ZERO_DIVISION_ERROR_CODE);
	Unlint numerator = *this;
	numerator.negative = false;
	while (true)
	{
		Unlint divider = other;
		divider.negative = false;
		if (divider > numerator)
			return numerator.antidrain();
		int64_t counter = numerator.distance(divider) - 1;
		while (numerator >= divider.move10(++counter));//FIXIT
		divider.movethis10(counter - 1);
		while (numerator >= divider)
			numerator -= divider;
	}
}

Unlint& Unlint::operator%=(const Unlint& other)
{
	if (other.zero())
		throw ZERO_DIVISION_ERROR_CODE;
		//exit(ZERO_DIVISION_ERROR_CODE);
	this->negative = false;
	while (true)
	{
		Unlint divider = other;
		divider.negative = false;
		if (divider > *this)
			return this->antidrain();
		int64_t counter = this->distance(divider) - 1;
		while (*this >= divider.move10(++counter));//FIXIT
		divider.movethis10(counter - 1);
		while (*this >= divider)
			*this -= divider;
	}
}


Unlint Unlint::operator-()const
{
	Unlint result = *this;
	result.negative = !this->negative;
	return result;

}


uint64_t Unlint::getsize()const
{
	return sizeof(bool) + sizeof(uint32_t) * ((uint64_t)this->len + 1);
}

Unlint abs(const Unlint& value)
{
	Unlint result = value;
	result.negative = false;
	return result;
}

Unlint sign(const Unlint& value)
{
	if (value.zero())
		return 0;
	if (value.negative)
		return -1;
	return 1;
}

char getcharfromint(const uint32_t& value, const char& index)
{
	uint32_t a = value;
	char length = 0;
	while (length != index)
	{
		a /= 10;
		length++;
	}
	return a % 10 + '0';
}

char* cstring(const Unlint& value)
{
	char* str = new char[(uint64_t(value.len - 1)) * 9 + length_int(value.num[value.len - 1]) + 1 + value.negative];
	bool zeros = true;
	uint64_t index = 0;
	if (value.negative)
		str[index++] = '-';
	for (char j = 8;; j--)
	{
		if (getcharfromint(value.num[value.len - 1], j) != '0' || !zeros)
		{
			str[index++] = getcharfromint(value.num[value.len - 1], j);
			zeros = false;
		}
		if (j == 0)break;
	}
	for (uint32_t i = value.len - 2; ; i--)
	{
		for (char j = 8;; j--)
		{
			str[index++] = getcharfromint(value.num[i], j);
			if (j == 0)break;
		}
		if (i == 0)break;
	}
	str[index] = 0;
	return str;
}

char* bytes(const Unlint& value)
{
	uint32_t index = 0;
	char* byte = new char[value.getsize()]{};
	byte[index++] = char(value.negative);
	char* buff = (char*)&value.len;
	for (uint8_t i = 0; i < sizeof(uint32_t); i++)
		byte[index++] = buff[i];
	for (uint32_t i = 0; i < value.len; i++)
	{
		buff = (char*)&value.num[i];
		for (uint8_t j = 0; j < sizeof(uint32_t); j++)
			byte[index++] = buff[j];
	}

	return byte;
}

Unlint gcd(const Unlint& value1, const Unlint& value2)
{
	Unlint n1 = abs(value1);
	Unlint n2 = abs(value2);
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


