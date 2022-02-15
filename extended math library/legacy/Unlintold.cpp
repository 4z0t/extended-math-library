#include "Unlint.h"
//#include <bitset>

//int abs(const int& value)
//{
//    if(value<0)
//        return -value;
//    return value;
//}

Unlint Unlint::cut(const uint32_t& length)
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
	while (a != 0)
	{
		a /= 10;
		length++;
	}
	return length;
}
int pow10(const int& value)
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

bool  Unlint::operator==(const Unlint& other)
{
	if (this->negative != other.negative)
		return false;
	if (this->len > other.len)
	{
		for (uint32_t i = this->len - 1;; i--)
			if (other.len > i)
			{
				if (this->num[i] != other.num[i])
					return  false;
				if (i == 0)
					break;
			}
			else
			{
				if (this->num[i] != 0)
					return  false;
			}
	}
	else
	{
		for (uint32_t i = other.len - 1;; i--)
			if (this->len > i)
			{
				if (this->num[i] != other.num[i])
					return  false;
				if (i == 0)
					break;
			}
			else
			{
				if (other.num[i] != 0)
					return  false;

			}
	}
	return true;
}



bool  Unlint::operator!=(const Unlint& other)
{
	return !(*this == other);
}

bool Unlint::operator>(const Unlint& other)
{
	if (!this->negative && other.negative)
		return true;
	if (this->negative && !other.negative)
		return false;

	return ((!(this->negative && other.negative)) == (*this >> other)) && ((*this) != other);
}

bool Unlint::operator>=(const Unlint& other)
{
	if (!this->negative && other.negative)
		return true;
	if (this->negative && !other.negative)
		return false;

	return ((!(this->negative && other.negative)) == (*this >> other)) || (*this == other);
}
//#ifdef _INITIALIZER_LIST_
//Unlint::Unlint(std::initializer_list<uint32_t> num)
//{
//	this->len = num.size();
//	this->num = new uint32_t[this->len]{};
//	int  j = this->len;
//	for (uint32_t i : num)
//		this->num[--j] = i;
//}
//
//Unlint::Unlint(std::initializer_list<uint32_t> num, bool negative)
//{
//	this->negative = negative;
//	this->len = num.size();
//	this->num = new uint32_t[this->len]{};
//	int  j = this->len;
//	for (uint32_t i : num)
//		this->num[--j] = i;
//}
//#endif
Unlint::Unlint(const uint32_t& num_len, bool negative)
{
	this->negative = negative;
	this->len = num_len;
	this->num = new uint32_t[this->len]{};
}

Unlint::Unlint()
{
	this->len = 0;
	this->num = nullptr;
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

void Unlint::antidrain()
{
	if (this->num[this->len - 1] == 0)
	{
		for (uint32_t i = this->len - 1; ; i--)
			if (this->num[i] != 0 || i == 0)
			{
				this->len = i + 1;
				break;
			}
		uint32_t* new_num = new uint32_t[this->len]{};
		for (uint32_t i = 0; i < this->len; i++)
			new_num[i] = this->num[i];
		delete[] this->num;
		this->num = new_num;
	}
}

Unlint::Unlint(const Unlint& other)
{
	for (int i = other.len - 1; i >= 0; i--)
		if (other.num[i] != 0)
		{
			this->len = i + 1;
			break;
		}
		else
			this->len = 1;

	this->negative = other.negative;
	this->num = new uint32_t[this->len]{};
	for (uint32_t i = 0; i < this->len; i++)
		this->num[i] = other.num[i];
}

Unlint::Unlint(const uint32_t* num, const uint32_t& len, bool negative)
{
	this->negative = negative;
	this->len = len;
	this->num = new uint32_t[len]{};
	for (uint32_t i = 0; i < len; i++)
		this->num[i] = num[len - i - 1];
}

Unlint::~Unlint()
{
	if (this->num != nullptr)
		delete[] this->num;
}

Unlint Unlint::move10(const uint32_t& times)
{
	Unlint new_unlint(this->len + times / 9 + 1, this->negative);
	for (uint32_t i = 0; i < this->len; i++)
	{
		new_unlint.num[i + times / 9] += (this->num[i] % pow10(9 - times % 9)) * pow10(times % 9);
		new_unlint.num[i + times / 9 + 1] += this->num[i] / pow10(9 - times % 9);
	}
	return new_unlint;
}

Unlint Unlint::move10(const uint32_t& times) const
{
	Unlint new_unlint(this->len + times / 9 + 1, this->negative);
	for (uint32_t i = 0; i < this->len; i++)
	{
		new_unlint.num[i + times / 9] += (this->num[i] % pow10(9 - times % 9)) * pow10(times % 9);
		new_unlint.num[i + times / 9 + 1] += this->num[i] / pow10(9 - times % 9);
	}
	return new_unlint;
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


//Unlint Unlint::movecells(const uint32_t& length)
//{
//	if (length)
//	{
//		Unlint new_unlint(this->len + length, this->negative);
//		for (uint32_t i = 0; i < this->len; i++)
//			new_unlint.num[i + length] = this->num[i];
//		return new_unlint;
//	}
//	return *this;
//}

//uint32_t cut(const uint32_t& value,const int& digits)
//{
//    return value%pow10(digits);
//}

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
	return *this;
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
	Unlint result = other;
	return result * result;
}

Unlint pow(const Unlint& other, const uint32_t& n)
{
	Unlint result = 1;
	Unlint buffer = other;
	for (uint8_t i = 0; i < sizeof(n) * 8 && (1 << i) <= n; i++)
	{
		//std::cout << i << std::endl;
		if (n & (1 << i))
			result = buffer * result;
		if ((1 << (i + 1)) < n)
			buffer = buffer * buffer;
	}
	return result;
}

Unlint sqrt(const Unlint& value)
{
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
//	for (uint32_t i = 0; i < this->len * 9; i++)
//		for (uint32_t j = 0; j < other.len * 9; j++)
//		{
//			if (this->num[i / 9] != 0 && other.num[j / 9] != 0)
//			{
//				uint32_t a = niv(this->num[i / 9], i % 9);
//				uint32_t b = niv(other.num[j / 9], j % 9);
//				if (a != 0 && b != 0)
//				{
//					if (a * b >= 10)
//					{
//						result.num[(i + j) / 9] += niv(a * b, 0) * pow10((i + j) % 9);
//						result.num[(i + j) / 9 + 1] += result.num[(i + j) / 9] / milrd;
//						result.num[(i + j) / 9] %= milrd;
//						result.num[(i + j + 1) / 9] += niv(a * b, 1) * pow10((i + j + 1) % 9);
//						result.num[(i + j + 1) / 9 + 1] += result.num[(i + j + 1) / 9] / milrd;
//						result.num[(i + j + 1) / 9] %= milrd;
//					}
//					else
//					{
//						result.num[(i + j) / 9] += a * b * pow10((i + j) % 9);
//						result.num[(i + j) / 9 + 1] += result.num[(i + j) / 9] / milrd;
//						result.num[(i + j) / 9] %= milrd;
//					}
//				}
//			}
//		}
//	return result;
//}

Unlint Unlint::operator*(const Unlint& other)
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
	return result;
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

//Unlint Unlint::operator*(const int &value)
//{
//    return (*this) * Unlint(value);
//}

Unlint Unlint::operator-(const Unlint& other)
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
			return result;
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

			return result;
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

			return result;
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

			return result;
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
					int j = i + 1;
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
		exit(0);
	bool numsign = this->negative != other.negative;
	Unlint result = 0;
	while (true)
	{
		Unlint divider = other;
		divider.negative = false;
		Unlint step = 1;
		if (divider > *this)
			break;

		int counter = this->distance(divider) - 1;
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

Unlint Unlint::operator+(const Unlint& other)
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
		return result;
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

			return result;
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
					int j = i + 1;
					while (result.num[j] == 0)
					{
						result.num[j++] = milrd - 1;
						if (j == result.len)
							break;
					}
					result.num[j] -= 1;
					result.num[i] += milrd - this->num[i];
				}
			return result;
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
						int j = i + 1;
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

bool  Unlint::operator>>(const Unlint& other)
{
	if (this->len > other.len)
	{
		for (uint32_t i = this->len - 1; ; i--)
			if (other.len > i)
			{
				if (this->num[i] != other.num[i])
					return  this->num[i] > other.num[i];
				if (i == 0)
					break;
			}
			else
			{
				if (this->num[i] != 0)
					return  true;
			}
	}
	else
	{
		for (uint32_t i = other.len - 1;; i--)
			if (this->len > i)
			{
				if (this->num[i] != other.num[i])
					return  this->num[i] > other.num[i];
				if (i == 0)
					break;
			}
			else
			{
				if (other.num[i] != 0)
					return  false;
			}
	}
	return true;
}

bool  Unlint::operator<<(const Unlint& other)
{
	if (this->len > other.len)
	{
		for (uint32_t i = this->len - 1; ; i--)
			if (other.len > i)
			{
				if (this->num[i] != other.num[i])
					return  this->num[i] < other.num[i];
				if (i == 0)
					break;
			}
			else
			{
				if (this->num[i] != 0)
					return  false;
			}
	}
	else
	{
		for (uint32_t i = other.len - 1; ; i--)
			if (this->len > i)
			{
				if (this->num[i] != other.num[i])
					return  this->num[i] < other.num[i];
				if (i == 0)
					break;
			}
			else
			{
				if (other.num[i] != 0)
					return  true;
			}
	}
	return false;
}

bool Unlint::zero()
{
	for (uint32_t i = 0; i < this->len; i++)
		if (this->num[i] != 0)
			return false;
	return true;
}

bool Unlint::zero()const
{
	for (uint32_t i = 0; i < this->len; i++)
		if (this->num[i] != 0)
			return false;
	return true;
}

Unlint& Unlint::operator++()
{
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
	return *this;
}


Unlint& Unlint::operator++(int)
{
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
	return *this;
}

Unlint& Unlint::operator--()
{
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
	return *this;
}

Unlint& Unlint::operator--(int)
{
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
	return *this;
}

Unlint::Unlint(const int& value)
{
	if (value >= milrd)
	{
		this->negative = (value < 0);
		this->num = new uint32_t[this->len = 2]{};
		this->num[0] = abs(value) % milrd;
		this->num[1] = abs(value) / milrd;
	}
	else
	{
		this->negative = (value < 0);
		this->num = new uint32_t[this->len = 1]{};
		this->num[0] = abs(value);
	}
}

int Unlint::distance(const Unlint& other)
{
	uint32_t result;
	for (uint32_t i = this->len - 1;; i--)
		if (this->num[i] != 0 || i == 0)
		{
			result = length_int(this->num[i]) + i * 9;
			break;
		}


	for (uint32_t i = other.len - 1; ; i--)
		if (other.num[i] != 0 || i == 0)
		{
			result -= length_int(other.num[i]) + i * 9;
			break;
		}

	return result;

}

Unlint Unlint::operator/(const Unlint& other)
{
	if (other.zero())
		exit(0);
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

		int counter = numerator.distance(divider) - 1;
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
	return result;
}

Unlint Unlint::operator/(const Unlint& other)const
{
	if (other.zero())
		exit(0);
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

		int counter = numerator.distance(divider) - 1;
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
	return result;
}

Unlint Unlint::operator%(const Unlint& other)
{
	if (other.zero())
		exit(0);
	Unlint numerator = *this;
	numerator.negative = false;
	while (true)
	{
		Unlint divider = other;
		divider.negative = false;
		if (divider > numerator)
			break;
		int counter = numerator.distance(divider) - 1;
		while (numerator >= divider.move10(++counter));//FIXIT

//        while(numerator >= divider)
//        {
//            divider = divider.move10(1);
//            counter++;
//        }
//        divider = other.move10(counter - 1);
//        divider.negative = false;
		divider.movethis10(counter - 1);
		for (int multiplier = 2; multiplier <= 10; multiplier++)
		{
			if (divider * multiplier > numerator)
			{
				numerator -= divider * (multiplier - 1);
				break;
			}
		}
	}
	return numerator;
}

Unlint Unlint::operator-()
{
	Unlint result = *this;
	result.negative = !this->negative;
	return result;

}

uint64_t Unlint::getsize()
{
	return sizeof(bool) + sizeof(uint32_t) * (this->len + 1);
}

uint64_t Unlint::getsize()const
{
	return sizeof(bool) + sizeof(uint32_t) * (this->len + 1);
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

char getcharfromint(uint32_t& value, char index)
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
		if (n1 > n2)
			n1 = n1 % n2;
		else
			n2 = n2 % n1;
		if (n1.zero() || n2.zero())
			return n1 + n2;
	}

	return n1;
}