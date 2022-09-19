#pragma once
#ifndef FLOAT_BASE_H
#define FLOAT_BASE_H

#include <stdlib.h>
#include <stdint.h>
#include <math.h>



template <typename T >
class FloatBase
{
public:

	FloatBase();
	~FloatBase();
	FloatBase(const FloatBase& other);
	FloatBase(const T& other);
	FloatBase(const float& value);
	FloatBase(const double& value);
	FloatBase(const T& other, const uint32_t& _precision, bool domove = true);

	FloatBase operator*(const FloatBase& other)const;
	FloatBase operator+(const FloatBase& other)const;
	FloatBase operator-(const FloatBase& other)const;

	
	FloatBase operator/(const T& other)const;
	FloatBase operator/(const FloatBase& other)const;
	
	

	explicit operator double()const;
	explicit operator float()const;

	FloatBase& operator+=(const FloatBase& other);
	FloatBase& operator+=(const T& other);
	

	FloatBase& operator-=(const FloatBase& other);
	FloatBase& operator-=(const T& other);
	

	FloatBase& operator/=(const FloatBase& other);
	FloatBase& operator/=(const T& other);
	

	FloatBase& operator*=(const FloatBase& other);
	FloatBase& operator*=(const T& other);
	

	FloatBase& operator=(const FloatBase& other);

	FloatBase operator-()const;

	bool operator==(const FloatBase& other)const;
	bool operator!=(const FloatBase& other)const;
	bool operator>(const FloatBase& other)const;
	bool operator<(const FloatBase& other)const;
	bool operator>=(const FloatBase& other)const;
	bool operator<=(const FloatBase& other)const;

	static void set_precision(const uint32_t& _precision);
	static uint32_t get_precision();


#ifdef _IOSTREAM_
	friend std::ostream& operator<<(std::ostream& os, const FloatBase& value);
#endif

protected:
	static const uint32_t BASIC_PRECISION = 10;
	static  uint32_t settable_precision;
	static bool is_set;

	uint32_t _precision;
	T _int;

};

template <typename T>
uint32_t FloatBase<T>::settable_precision = FloatBase<T>::BASIC_PRECISION;
template <typename T>
bool FloatBase<T>::is_set = false;



template <typename T>
FloatBase<T>::FloatBase<T>()
{
	this->_int = 0;
	this->_precision = BASIC_PRECISION;
}

template <typename T>
FloatBase<T>::~FloatBase<T>()
{

}

template <typename T>
FloatBase<T>::FloatBase<T>(const FloatBase<T>& other)
{
	this->_int = other._int;
	this->_precision = other._precision;
}


template <typename T>
FloatBase<T>::FloatBase<T>(const T& other, const uint32_t& accur, bool domove)
{
	if (domove)
	{
		this->_int = other.movecells(this->_precision = accur);
	}
	else
	{
		this->_precision = accur;
		this->_int = other;
	}
}




template <typename T>
FloatBase<T>::FloatBase<T>(const T& other)
{
	this->_int = other.movecells(this->_precision = FloatBase<T>::get_precision());
}

template <typename T>
void FloatBase<T>::set_precision(const uint32_t& accur)
{
	settable_precision = accur;
	is_set = true;
}

template <typename T>
uint32_t FloatBase<T>::get_precision()
{
	if (is_set)
		return settable_precision;
	return BASIC_PRECISION;
}

template <typename T>
FloatBase<T> FloatBase<T>::operator+(const FloatBase<T>& other)const
{
	if (this->_precision == other._precision)
	{
		return FloatBase<T>(this->_int + other._int, this->_precision, false);
	}
	if (this->_precision > other._precision)
	{
		return FloatBase<T>(this->_int.cut(this->_precision - other._precision) + other._int, other._precision, false);
	}
	return FloatBase<T>(this->_int + other._int.cut(other._precision - this->_precision), this->_precision, false);
}

template <typename T>
FloatBase<T> FloatBase<T>::operator-(const FloatBase<T>& other)const
{
	if (this->_precision == other._precision)
	{
		return FloatBase<T>(this->_int - other._int, this->_precision, false);
	}
	if (this->_precision > other._precision)
	{
		return FloatBase<T>(this->_int.cut(this->_precision - other._precision) - other._int, other._precision, false);
	}
	return FloatBase<T>(this->_int - other._int.cut(other._precision - this->_precision), this->_precision, false);
}

template <typename T>
FloatBase<T> FloatBase<T>::operator*(const FloatBase<T>& other)const
{
	return FloatBase<T>((this->_int * other._int).cut((this->_precision > other._precision) ? this->_precision : other._precision),
		(this->_precision < other._precision) ? this->_precision : other._precision, false);
	//return FloatBase<T>(this->_int*other._int,this->_precision + other._precision,false);//mb we should apply less _precision...
}


template <typename T>
FloatBase<T> FloatBase<T>::operator/(const FloatBase<T>& other)const
{
	return FloatBase<T>(((this->_int.movecells(other._precision)) / other._int), this->_precision, false);
}

template <typename T>
FloatBase<T> FloatBase<T>::operator/(const T& other)const
{
	return FloatBase<T>(this->_int / other, this->_precision, false);
}


template <typename T>
FloatBase<T> FloatBase<T>::operator-()const
{
	return FloatBase<T>(-this->_int, this->_precision, false);
}
template <typename T>
bool FloatBase<T>::operator==(const FloatBase<T>& other)const
{
	if (this->_precision == other._precision)
		return this->_int == other._int;
	if (this->_precision > other._precision)
		return this->_int == other._int.movecells(this->_precision - other._precision);
	return this->_int.movecells(other._precision - this->_precision) == other._int;
}
template <typename T>
bool FloatBase<T>::operator!=(const FloatBase<T>& other)const
{
	return !(*this == other);
}
template <typename T>
bool FloatBase<T>::operator>(const FloatBase<T>& other)const
{
	if (this->_precision == other._precision)
		return this->_int > other._int;
	if (this->_precision > other._precision)
		return this->_int > other._int.movecells(this->_precision - other._precision);
	return this->_int.movecells(other._precision - this->_precision) > other._int;
}
template <typename T>
bool FloatBase<T>::operator<(const FloatBase<T>& other)const
{
	if (this->_precision == other._precision)
		return this->_int < other._int;
	if (this->_precision > other._precision)
		return this->_int < other._int.movecells(this->_precision - other._precision);
	return this->_int.movecells(other._precision - this->_precision) < other._int;
}
template <typename T>
bool FloatBase<T>::operator>=(const FloatBase<T>& other)const
{
	if (this->_precision == other._precision)
		return this->_int >= other._int;
	if (this->_precision > other._precision)
		return this->_int >= other._int.movecells(this->_precision - other._precision);
	return this->_int.movecells(other._precision - this->_precision) >= other._int;
}
template <typename T>
bool FloatBase<T>::operator<=(const FloatBase<T>& other)const
{
	if (this->_precision == other._precision)
		return this->_int <= other._int;
	if (this->_precision > other._precision)
		return this->_int <= other._int.movecells(this->_precision - other._precision);
	return this->_int.movecells(other._precision - this->_precision) <= other._int;
}


template <typename T>
FloatBase<T>& FloatBase<T>::operator=(const FloatBase<T>& other)
{
	this->_int = other._int;
	this->_precision = other._precision;
	return *this;
}

template <typename T>
FloatBase<T>& FloatBase<T>::operator+=(const T& other)
{
	this->_int += other.movecells(this->_precision);
	return *this;
}

template <typename T>
FloatBase<T>& FloatBase<T>::operator-=(const T& other)
{
	this->_int -= other.movecells(this->_precision);
	return *this;
}

template <typename T>
FloatBase<T>& FloatBase<T>::operator+=(const FloatBase<T>& other)
{
	if (this->_precision == other._precision)
	{
		this->_int += other._int;
	}
	else if (this->_precision > other._precision)
	{
		this->_int.cutthis(this->_precision - other._precision) += other._int;
	}
	else
	{
		this->_int += other._int.cut(other._precision - this->_precision);
	}
	this->_precision = (this->_precision >= other._precision) ? other._precision : this->_precision;
	return *this;
}
template <typename T>
FloatBase<T>& FloatBase<T>::operator-=(const FloatBase<T>& other)
{
	if (this->_precision == other._precision)
	{
		this->_int -= other._int;
	}
	else if (this->_precision > other._precision)
	{
		this->_int.cutthis(this->_precision - other._precision) -= other._int;
	}
	else
	{
		this->_int -= other._int.cut(other._precision - this->_precision);
	}
	this->_precision = (this->_precision >= other._precision) ? other._precision : this->_precision;
	return *this;
}
template <typename T>
FloatBase<T>& FloatBase<T>::operator*=(const FloatBase<T>& other)
{
	if (this->_precision >= other._precision)
	{
		(this->_int *= other._int).cutthis(this->_precision);
	}
	else
	{
		(this->_int *= other._int).cutthis(other._precision);
	}
	this->_precision = (this->_precision >= other._precision) ? other._precision : this->_precision;
	return *this;
}

template <typename T>
FloatBase<T>& FloatBase<T>::operator*=(const T& other)
{
	this->_int *= other;
	return *this;
}

template <typename T>
FloatBase<T> operator*(const uint32_t& value, const FloatBase<T>& other)
{
	return other * value;
}

template <typename T>
FloatBase<T>& FloatBase<T>::operator/=(const FloatBase<T>& other)
{
	this->_int = this->_int.movecells(other._precision) / other._int;
	return *this;
}
template <typename T>
FloatBase<T>& FloatBase<T>::operator/=(const T& other)
{
	this->_int /= other;
	return *this;
}

template <typename T>
FloatBase<T> sqrt(const FloatBase<T>& value)
{
	FloatBase<T> prev = 0;
	FloatBase<T> res = value;
	while (prev != res)
	{
		prev = res;
		res = (res + value / res) / 2;
	}
	return res;
}
template <typename T>
FloatBase<T> pow(const FloatBase<T>& other, const uint32_t& n)
{
	FloatBase<T> result = 1;
	FloatBase<T> buffer = other;
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
template <typename T>
FloatBase<T>::operator float() const
{
	FloatBase<T> buffer = abs(*this);
	uint8_t exponent = 127;
	if (this->_int.distance() > (uint64_t)this->_precision * 9)
	{
		while (buffer._int.distance() > (uint64_t)(buffer._precision) * 9)
		{
			buffer /= 2;
			exponent++;
			if (exponent == UINT8_MAX)
			{
				if (this->_int._sign)
					return -INFINITY;
				return INFINITY;
			}
		}
		buffer *= 2;
		exponent--;
	}
	else
	{
		while (buffer._int.distance() <= (uint64_t)buffer._precision * 9)
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
	if (this->_int._sign)
		r |= (1u << 31);
	//std::memcpy(&result, &r, sizeof result);

	return *(float*)&r;
}

template <typename T>
FloatBase<T>::operator double() const
{
	FloatBase<T> buffer = abs(*this);
	uint16_t exponent = 1023;
	if (this->_int.distance() > (uint64_t)this->_precision * 9)
	{
		while (buffer._int.distance() > (uint64_t)(buffer._precision) * 9)
		{
			buffer /= 2;
			exponent++;
			if (exponent == 2047)
			{
				if (this->_int._sign)
					return -INFINITY;
				return INFINITY;
			}
		}
		buffer *= 2;
		exponent--;
	}
	else
	{
		while (buffer._int.distance() <= (uint64_t)buffer._precision * 9)
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
	if (this->_int._sign)
		r |= (1ull << 63);
	//std::memcpy(&result, &r, sizeof result);

	return *(double*)&r;
}

#endif // !FLOAT_BASE_H