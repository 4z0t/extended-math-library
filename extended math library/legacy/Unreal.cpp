#include "Unreal.h"
class Fraction;

bool Unreal::isset = false;
uint32_t Unreal::settable_precision = 0;

Unreal::Unreal()
{
	this->number = 0;
	this->precision = basic_precision;
}

Unreal::~Unreal()
{

}

Unreal::Unreal(const Unreal& other)
{
	this->number = other.number;
	this->precision = other.precision;
}


Unreal::Unreal(const Unlint& other, const uint32_t& accur, bool domove)
{
	if (domove)
	{
		this->number = other.movecells(this->precision = accur);
	}
	else
	{
		this->precision = accur;
		this->number = other;
	}
}

Unreal::Unreal(const int& value)
{
	this->number = Unlint(value).movecells(this->precision = Unreal::get_precision());
}
#ifdef FRACTION_H
Unreal::Unreal(const float& value)
{
	//uint32_t val = reinterpret_cast<uint32_t>(value);
	uint32_t val = *(uint32_t*)&value;
	*this = 1;
	bool sign = (val >> 31);
	val &= 0x7fffffffu;
	*this += ~Fraction(Unlint(val&0x007fffffu),Unlint(1u<<23));
	int power = int(val >> 23) - 127;
	*this *= ~pow(Fraction(2), power);
	this->number.negative = sign;
}

Unreal::Unreal(const double& value)
{
	uint64_t val = *(uint64_t*)&value;
	*this = 1;
	bool sign = (val >> 63);
	val &= 0x7fffffffffffffffull;
	*this += ~Fraction(Unlint(val & 0x000fffffffffffffull), Unlint(1ull << 52));
	int power = int(val >> 52) - 1023;
	*this *= ~pow(Fraction(2), power);
	this->number.negative = sign;//64th bit of sign;
}
#endif // DEBUG

Unreal::Unreal(const Unlint& other)
{
	this->number = other.movecells(this->precision = Unreal::get_precision());
}

void Unreal::set_precision(const uint32_t& accur)
{
	settable_precision = accur;
	isset = true;
}

uint32_t Unreal::get_precision()
{
	if (isset)
		return settable_precision;
	return basic_precision;
}

Unreal Unreal::operator+(const Unreal& other)const
{
	if (this->precision == other.precision)
	{
		return Unreal(this->number + other.number, this->precision, false);
	}
	if (this->precision > other.precision)
	{
		return Unreal(this->number.cut(this->precision - other.precision) + other.number, other.precision, false);
	}
	return Unreal(this->number + other.number.cut(other.precision - this->precision), this->precision, false);
}

Unreal Unreal::operator-(const Unreal& other)const
{
	if (this->precision == other.precision)
	{
		return Unreal(this->number - other.number, this->precision, false);
	}
	if (this->precision > other.precision)
	{
		return Unreal(this->number.cut(this->precision - other.precision) - other.number, other.precision, false);
	}
	return Unreal(this->number - other.number.cut(other.precision - this->precision), this->precision, false);
}

Unreal Unreal::operator*(const Unreal& other)const
{
	return Unreal((this->number * other.number).cut((this->precision > other.precision) ? this->precision : other.precision),
		(this->precision < other.precision) ? this->precision : other.precision, false);
	//return Unreal(this->number*other.number,this->precision + other.precision,false);//mb we should apply less precision...
}

Unreal Unreal::operator*(const uint32_t& other) const
{
	return Unreal(this->number * other, this->precision, false);
}


Unreal Unreal::operator/(const Unreal& other)const
{
	return Unreal(((this->number.movecells(other.precision)) / other.number), this->precision, false);
}


Unreal Unreal::operator/(const Unlint& other)const
{
	return Unreal(this->number / other, this->precision, false);
}


Unreal Unreal::operator/(const int& other)const
{
	return Unreal(this->number / other, this->precision, false);
}

Unreal Unreal::operator-()const
{
	return Unreal(-this->number, this->precision, false);
}

bool Unreal::operator==(const Unreal& other)const
{
	if (this->precision == other.precision)
		return this->number == other.number;
	if (this->precision > other.precision)
		return this->number == other.number.movecells(this->precision - other.precision);
	return this->number.movecells(other.precision - this->precision) == other.number;
}

bool Unreal::operator!=(const Unreal& other)const
{
	return !(*this == other);
}

bool Unreal::operator>(const Unreal& other)const
{
	if (this->precision == other.precision)
		return this->number > other.number;
	if (this->precision > other.precision)
		return this->number > other.number.movecells(this->precision - other.precision);
	return this->number.movecells(other.precision - this->precision) > other.number;
}

bool Unreal::operator<(const Unreal& other)const
{
	if (this->precision == other.precision)
		return this->number < other.number;
	if (this->precision > other.precision)
		return this->number < other.number.movecells(this->precision - other.precision);
	return this->number.movecells(other.precision - this->precision) < other.number;
}

bool Unreal::operator>=(const Unreal& other)const
{
	if (this->precision == other.precision)
		return this->number >= other.number;
	if (this->precision > other.precision)
		return this->number >= other.number.movecells(this->precision - other.precision);
	return this->number.movecells(other.precision - this->precision) >= other.number;
}

bool Unreal::operator<=(const Unreal& other)const
{
	if (this->precision == other.precision)
		return this->number <= other.number;
	if (this->precision > other.precision)
		return this->number <= other.number.movecells(this->precision - other.precision);
	return this->number.movecells(other.precision - this->precision) <= other.number;
}



Unreal& Unreal::operator=(const Unreal& other)
{
	this->number = other.number;
	this->precision = other.precision;
	return *this;
}


Unreal& Unreal::operator+=(const Unlint& other)
{
	this->number += other.movecells(this->precision);
	return *this;
}

Unreal& Unreal::operator+=(const int& other)
{
	this->number += Unlint(other).movecells(this->precision);
	return *this;
}
Unreal& Unreal::operator-=(const Unlint& other)
{
	this->number -= other.movecells(this->precision);
	return *this;
}

Unreal& Unreal::operator-=(const int& other)
{
	this->number -= Unlint(other).movecells(this->precision);
	return *this;
}

Unreal& Unreal::operator+=(const Unreal& other)
{
	if (this->precision == other.precision)
	{
		this->number += other.number;
	}
	else if (this->precision > other.precision)
	{
		this->number.cutthis(this->precision - other.precision) += other.number;
	}
	else
	{
		this->number += other.number.cut(other.precision - this->precision);
	}
	this->precision = (this->precision >= other.precision) ? other.precision : this->precision;
	return *this;
}

Unreal& Unreal::operator-=(const Unreal& other)
{
	if (this->precision == other.precision)
	{
		this->number -= other.number;
	}
	else if (this->precision > other.precision)
	{
		this->number.cutthis(this->precision - other.precision) -= other.number;
	}
	else
	{
		this->number -= other.number.cut(other.precision - this->precision);
	}
	this->precision = (this->precision >= other.precision) ? other.precision : this->precision;
	return *this;
}

Unreal& Unreal::operator*=(const Unreal& other)
{
	if (this->precision >= other.precision)
	{
		(this->number *= other.number).cutthis(this->precision);
	}
	else
	{
		(this->number *= other.number).cutthis(other.precision);
	}
	this->precision = (this->precision >= other.precision) ? other.precision : this->precision;
	return *this;
}


Unreal& Unreal::operator*=(const Unlint& other)
{
	this->number *= other;
	return *this;
}

Unreal& Unreal::operator*=(const int& other)
{
	this->number *= other;
	return *this;
}

Unreal operator*(const uint32_t& value, const Unreal& other)
{
	return other * value;
}


Unreal& Unreal::operator/=(const Unreal& other)
{
	this->number = this->number.movecells(other.precision) / other.number;
	return *this;
}

Unreal& Unreal::operator/=(const Unlint& other)
{
	this->number /= other;
	return *this;
}

Unreal& Unreal::operator/=(const int& other)
{
	this->number /= other;
	return *this;
}

Unreal sqrt(const Unreal& value)
{
	Unreal prev = 0;
	Unreal res = value;
	while (prev != res)
	{
		prev = res;
		res = (res + value / res) / 2;
	}
	return res;
}

Unreal pow(const Unreal& other, const uint32_t& n)
{
	Unreal result = 1;
	Unreal buffer = other;
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

Unreal::operator float() const
{
	Unreal buffer = abs(*this);
	uint8_t exponent = 127;
	if (this->number.distance() > (uint64_t)this->precision * 9)
	{
		while (buffer.number.distance() > (uint64_t)(buffer.precision) * 9)
		{
			buffer /= 2;
			exponent++;
			if (exponent == UINT8_MAX)
			{
				if (this->number.negative)
					return -INFINITY;
				return INFINITY;
			}
		}
		buffer *= 2;
		exponent--;
	}
	else
	{
		while (buffer.number.distance() <= (uint64_t)buffer.precision * 9)
		{
			buffer *= 2;
			exponent--;
			if (exponent == 0)
				return 0;//too small
		}
	}
	uint32_t r = 0;
	uint8_t d = 24;
	buffer -= 1;
	while (d)
	{
		d--;
		if (buffer >= 1)
		{
			r |= (1u << d);
			buffer -= 1;
		}
		buffer *= 2;
	}
	r |= (uint32_t)exponent << 23;
	if (this->number.negative)
		r |= (1u << 31);
	//std::memcpy(&result, &r, sizeof result);

	return *(float*)&r;
}


Unreal::operator double() const
{
	Unreal buffer = abs(*this);
	uint16_t exponent = 1023;
	if (this->number.distance() > (uint64_t)this->precision * 9)
	{
		while (buffer.number.distance() > (uint64_t)(buffer.precision) * 9)
		{
			buffer /= 2;
			exponent++;
			if (exponent == 2047)
			{
				if (this->number.negative)
					return -INFINITY;
				return INFINITY;
			}
		}
		buffer *= 2;
		exponent--;
	}
	else
	{
		while (buffer.number.distance() <= (uint64_t)buffer.precision * 9)
		{
			buffer *= 2;
			exponent--;
			if (exponent == 0)
				return 0;//too small
		}
	}
	uint64_t r = 0;
	uint8_t d = 53;
	buffer -= 1;
	while (d)
	{
		d--;
		if (buffer >= 1)
		{
			r |= (1ull << d);
			buffer -= 1;
		}
		buffer *= 2;
	}
	r |= (uint64_t)exponent << 52;
	if (this->number.negative)
		r |= (1ull << 63);
	//std::memcpy(&result, &r, sizeof result);

	return *(double*)&r;
}