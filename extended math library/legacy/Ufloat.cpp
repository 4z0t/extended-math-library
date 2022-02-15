#include "Ufloat.h"
#include <iostream>
using namespace std;


bool Ufloat::isset = false;
uint32_t Ufloat::settable_precision = 0;

Ufloat::Ufloat()
{
	this->number = 0;
	this->precision = basic_precision;
}

Ufloat::~Ufloat()
{

}

Ufloat::Ufloat(const Ufloat& other)
{
	this->number = other.number;
	this->precision = other.precision;
}


Ufloat::Ufloat(const Ubit& other, const uint32_t& accur, bool domove)
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

Ufloat::Ufloat(const int& value)
{
	this->number = Ubit(value).movecells(this->precision = Ufloat::get_precision());
}


Ufloat::Ufloat(const Ubit& other)
{
	this->number = other.movecells(this->precision = Ufloat::get_precision());
}

void Ufloat::set_precision(const uint32_t& accur)
{
	settable_precision = accur;
	isset = true;
}

uint32_t Ufloat::get_precision()
{
	if (isset)
		return settable_precision;
	return basic_precision;
}



Ufloat Ufloat::operator+(const Ufloat& other)const
{
	if (this->precision == other.precision)
	{
		return Ufloat(this->number + other.number, this->precision, false);
	}
	if (this->precision > other.precision)
	{
		return Ufloat(this->number.cut(this->precision - other.precision) + other.number, other.precision, false);
	}
	return Ufloat(this->number + other.number.cut(other.precision - this->precision), this->precision, false);
}

Ufloat Ufloat::operator-(const Ufloat& other)const
{
	if (this->precision == other.precision)
	{
		return Ufloat(this->number - other.number, this->precision, false);
	}
	if (this->precision > other.precision)
	{
		return Ufloat(this->number.cut(this->precision - other.precision) - other.number, other.precision, false);
	}
	return Ufloat(this->number - other.number.cut(other.precision - this->precision), this->precision, false);
}

Ufloat Ufloat::operator*(const Ufloat& other)const
{
	return Ufloat((this->number * other.number).cut((this->precision > other.precision) ? this->precision : other.precision),
		(this->precision < other.precision) ? this->precision : other.precision, false);
	//return Ufloat(this->number*other.number,this->precision + other.precision,false);//mb we should apply less precision...
}

Ufloat Ufloat::operator*(const uint32_t& other) const
{
	return Ufloat(this->number * other, this->precision, false);
}


Ufloat Ufloat::operator/(const Ufloat& other)const
{
	return Ufloat(this->number.movecells(other.precision) / other.number, this->precision, false);
}


Ufloat Ufloat::operator/(const Ubit& other)const
{
	return Ufloat(this->number / other, this->precision, false);
}


Ufloat Ufloat::operator/(const int& other)const
{
	return Ufloat(this->number / other, this->precision, false);
}

Ufloat Ufloat::operator-()const
{
	return Ufloat(-this->number, this->precision, false);
}

bool Ufloat::operator==(const Ufloat& other)const
{
	if (this->precision == other.precision)
		return this->number == other.number;
	if (this->precision > other.precision)
		return this->number == other.number.movecells(this->precision - other.precision);
	return this->number.movecells(other.precision - this->precision) == other.number;
}

bool Ufloat::operator!=(const Ufloat& other)const
{
	return !(*this == other);
}

bool Ufloat::operator>(const Ufloat& other)const
{
	if (this->precision == other.precision)
		return this->number > other.number;
	if (this->precision > other.precision)
		return this->number > other.number.movecells(this->precision - other.precision);
	return this->number.movecells(other.precision - this->precision) > other.number;
}

bool Ufloat::operator<(const Ufloat& other)const
{
	if (this->precision == other.precision)
		return this->number < other.number;
	if (this->precision > other.precision)
		return this->number < other.number.movecells(this->precision - other.precision);
	return this->number.movecells(other.precision - this->precision) < other.number;
}

bool Ufloat::operator>=(const Ufloat& other)const
{
	if (this->precision == other.precision)
		return this->number >= other.number;
	if (this->precision > other.precision)
		return this->number >= other.number.movecells(this->precision - other.precision);
	return this->number.movecells(other.precision - this->precision) >= other.number;
}

bool Ufloat::operator<=(const Ufloat& other)const
{
	if (this->precision == other.precision)
		return this->number <= other.number;
	if (this->precision > other.precision)
		return this->number <= other.number.movecells(this->precision - other.precision);
	return this->number.movecells(other.precision - this->precision) <= other.number;
}



Ufloat& Ufloat::operator=(const Ufloat& other)
{
	this->number = other.number;
	this->precision = other.precision;
	return *this;
}


Ufloat& Ufloat::operator+=(const Ubit& other)
{
	this->number += other.movecells(this->precision);
	return *this;
}

Ufloat& Ufloat::operator+=(const int& other)
{
	this->number += Ubit(other).movecells(this->precision);
	return *this;
}
Ufloat& Ufloat::operator-=(const Ubit& other)
{
	this->number -= other.movecells(this->precision);
	return *this;
}

Ufloat& Ufloat::operator-=(const int& other)
{
	this->number -= Ubit(other).movecells(this->precision);
	return *this;
}

Ufloat& Ufloat::operator+=(const Ufloat& other)
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

Ufloat& Ufloat::operator-=(const Ufloat& other)
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

Ufloat& Ufloat::operator*=(const Ufloat& other)
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


Ufloat& Ufloat::operator*=(const Ubit& other)
{
	this->number *= other;
	return *this;
}

Ufloat& Ufloat::operator*=(const int& other)
{
	this->number *= other;
	return *this;
}

Ufloat operator*(const uint32_t& value, const Ufloat& other)
{
	return other * value;
}


Ufloat& Ufloat::operator/=(const Ufloat& other)
{
	this->number = this->number.movecells(other.precision) / other.number;
	return *this;
}

Ufloat& Ufloat::operator/=(const Ubit& other)
{
	this->number /= other;
	return *this;
}

Ufloat& Ufloat::operator/=(const int& other)
{
	this->number /= other;
	return *this;
}



Ufloat pow(const Ufloat& other, const uint32_t& n)
{
	Ufloat result = 1;
	Ufloat buffer = other;
	for (uint8_t i = 0; i < sizeof(n) * 8 && (1 << i) <= n; i++)
	{
		if (n & (1 << i))
			result *= buffer;
		if ((1 << i) < n)
			buffer *= buffer;
	}
	return result;
}

Ufloat sqrt(const Ufloat& value)
{
	Ufloat prev = Ubit(0u);
	Ufloat res = value;
	while (prev != res)
	{
		prev = res;
		res = (value / res + res) / Ubit(2u);
	}
	return res;
}