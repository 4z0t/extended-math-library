#ifndef Ring_H
#define Ring_H
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#define NOT_PRIME_NUMBER_ERROR -1


template<uint32_t _base>
class Ring
{
	int32_t num;
	static int* reciprocals;
	static bool checked;
	static uint32_t total_objects;
	void prime_exit(const uint32_t& num)
	{
		if (!this->checked)
		{
			for (uint32_t i = 2; i <= (uint32_t)sqrt(num); i++)
				if (num % i == 0)
					exit(NOT_PRIME_NUMBER_ERROR);
			if (num == 0 || num == 1)
				exit(NOT_PRIME_NUMBER_ERROR);
			this->checked = true;
		}
	}
	void fillreciprocals()
	{
		if (this->reciprocals == nullptr)
		{
			this->reciprocals = new int[_base] {};
			this->reciprocals[1] = 1;
			for (uint32_t i = 2; i < _base; i++)
				this->reciprocals[i] = (_base - (_base / i) * this->reciprocals[_base % i] % _base) % _base;
		}
	}
public:

	Ring();

	Ring(const Ring& other);

	Ring(const int8_t& value);
	Ring(const uint8_t& value);

	Ring(const int16_t& value);
	Ring(const uint16_t& value);

	Ring(const int32_t& value);
	Ring(const uint32_t& value);

	Ring(const int64_t& value);
	Ring(const uint64_t& value);

	~Ring();

	Ring& operator=(const Ring& other);

	bool operator==(const Ring& other)const;
	bool operator!=(const Ring& other)const;
	bool operator>(const Ring& other)const;
	bool operator>=(const Ring& other)const;
	bool operator<(const Ring& other)const;
	bool operator<=(const Ring& other)const;

	Ring operator*(const Ring& other)const;
	Ring operator+(const Ring& other)const;
	Ring operator-(const Ring& other)const;
	Ring operator/(const Ring& other)const;


	Ring operator-()const;
	Ring operator~()const;

	Ring& operator+=(const Ring& other);
	Ring& operator-=(const Ring& other);
	Ring& operator*=(const Ring& other);
	Ring& operator/=(const Ring& other);

	template<class U, uint32_t __base> friend Ring<__base> operator==(const U& value, const Ring<__base>& other);
	template<class U, uint32_t __base> friend Ring<__base> operator>=(const U& value, const Ring<__base>& other);
	template<class U, uint32_t __base> friend Ring<__base> operator<=(const U& value, const Ring<__base>& other);
	template<class U, uint32_t __base> friend Ring<__base> operator!=(const U& value, const Ring<__base>& other);
	template<class U, uint32_t __base> friend Ring<__base> operator>(const U& value, const Ring<__base>& other);
	template<class U, uint32_t __base> friend Ring<__base> operator<(const U& value, const Ring<__base>& other);

	template<class U, uint32_t __base> friend Ring<__base> operator*(const U& value, const Ring<__base>& other);
	template<class U, uint32_t __base> friend Ring<__base> operator+(const U& value, const Ring<__base>& other);
	template<class U, uint32_t __base> friend Ring<__base> operator-(const U& value, const Ring<__base>& other);
	template<class U, uint32_t __base> friend Ring<__base> operator/(const U& value, const Ring<__base>& other);


	template<uint32_t __base> friend Ring<__base> reciprocal(const Ring<__base>& value);


#ifdef _IOSTREAM_
	friend inline std::ostream& operator<<(std::ostream& os, const Ring& value)
	{
		return os << value.num;
	}
#endif
};






template<uint32_t _base>
bool Ring<_base>::checked = false;

template<uint32_t _base>
int* Ring<_base>::reciprocals = nullptr;

template<uint32_t _base>
uint32_t Ring<_base> ::total_objects = 0;


template<uint32_t _base>
Ring<_base>::Ring()
{
	this->prime_exit(_base);
	this->fillreciprocals();
	this->num = 0;
	this->total_objects++;
}


template<uint32_t _base>
Ring<_base>::Ring(const Ring<_base>& other)
{
	this->num = other.num;
	this->total_objects++;
}

template<uint32_t _base>
Ring<_base>::Ring(const int32_t& value)
{
	this->prime_exit(_base);
	this->fillreciprocals();
	if (value >= 0)
		this->num = value % (int32_t)_base;
	else
		this->num = (value % (int32_t)_base) + _base;
	this->total_objects++;
}

template<uint32_t _base>
Ring<_base>::Ring(const uint32_t& value)
{
	this->prime_exit(_base);
	this->fillreciprocals();
	this->num = value % _base;
	this->total_objects++;
}



template<uint32_t _base>
Ring<_base>::~Ring()
{
	this->total_objects--;
	if (this->total_objects == 0)
	{
		delete[]this->reciprocals;
		this->reciprocals = nullptr;
//#ifdef _IOSTREAM_
//		std::cout << "memory cleared for " << _base << std::endl;
//#endif
	}
}

// overriding compare operators for standart numerics
template<class U, uint32_t _base>
Ring<_base> operator==(const U& value, const Ring<_base>& other)
{
	return Ring<_base>(value) == other;
}

template<class U, uint32_t _base>
Ring<_base> operator!=(const U& value, const Ring<_base>& other)
{
	return Ring<_base>(value) != other;
}

template<class U, uint32_t _base>
Ring<_base> operator>(const U& value, const Ring<_base>& other)
{
	return Ring<_base>(value) > other;
}

template<class U, uint32_t _base>
Ring<_base> operator<(const U& value, const Ring<_base>& other)
{
	return Ring<_base>(value) < other;
}

template<class U, uint32_t _base>
Ring<_base> operator>=(const U& value, const Ring<_base>& other)
{
	return Ring<_base>(value) >= other;
}

template<class U, uint32_t _base>
Ring<_base> operator<=(const U& value, const Ring<_base>& other)
{
	return Ring<_base>(value) <= other;
}
//



// overriding operators for standart numerics
template<class U, uint32_t _base>
Ring<_base> operator/(const U& value, const Ring<_base>& other)
{
	return Ring<_base>(value) / other;
}

template<class U, uint32_t _base>
Ring<_base> operator*(const U& value, const Ring<_base>& other)
{
	return Ring<_base>(value) * other;
}

template<class U, uint32_t _base>
Ring<_base> operator+(const U& value, const Ring<_base>& other)
{
	return Ring<_base>(value) + other;
}

template<class U, uint32_t _base>
Ring<_base> operator-(const U& value, const Ring<_base>& other)
{
	return Ring<_base>(value) - other;
}



template<uint32_t _base>
Ring<_base>& Ring<_base>::operator=(const Ring<_base>& other)
{
	this->num = other.num;
	return *this;
}

template<uint32_t _base>
Ring<_base> Ring<_base>::operator-() const
{
	if (this->num == 0)
		return 0;
	Ring<_base> result;
	result.num = _base - this->num;
	return result;
}

template<uint32_t _base>
Ring<_base> Ring<_base>::operator+(const Ring<_base>& other) const
{
	Ring<_base> result;
	result.num = (this->num + other.num) % _base;
	return result;
}

template<uint32_t _base>
Ring<_base> Ring<_base>::operator-(const Ring<_base>& other) const
{
	return *this + (-other);
}

template<uint32_t _base>
Ring<_base> Ring<_base>::operator*(const Ring<_base>& other) const
{
	Ring<_base> result;
	result.num = (this->num * other.num) % _base;
	return result;
}

template<uint32_t _base>
Ring<_base> Ring<_base>::operator/(const Ring<_base>& other) const
{
	if (other == 0)
		throw "zero division error";
	Ring<_base> result;
	result.num = (this->num * this->reciprocals[other.num]) % _base;
	return result;
}

template<uint32_t _base>
Ring<_base> Ring<_base>::operator~() const
{
	Ring<_base> result;
	result.num = this->reciprocals[this->num];
	return result;
}

template<uint32_t _base>
Ring<_base> reciprocal(const Ring<_base>& value)
{
	Ring<_base> result;
	result.num = value.reciprocals[value.num];
	return result;
}


template<uint32_t _base>
Ring<_base>& Ring<_base>::operator/=(const Ring<_base>& other)
{
	return *this = *this / other;
}

template<uint32_t _base>
Ring<_base>& Ring<_base>::operator*=(const Ring<_base>& other)
{
	return *this = *this * other;
}

template<uint32_t _base>
Ring<_base>& Ring<_base>::operator-=(const Ring<_base>& other)
{
	return *this = *this - other;
}

template<uint32_t _base>
Ring<_base>& Ring<_base>::operator+=(const Ring<_base>& other)
{
	return *this = *this + other;
}

template<uint32_t _base>
bool Ring<_base>::operator==(const Ring<_base>& other)const
{
	return this->num == other.num;
}

template<uint32_t _base>
bool Ring<_base>::operator!=(const Ring<_base>& other)const
{
	return this->num != other.num;
}

template<uint32_t _base>
bool Ring<_base>::operator>=(const Ring<_base>& other)const
{
	return this->num == other.num;
}

template<uint32_t _base>
bool Ring<_base>::operator<=(const Ring<_base>& other)const
{
	return this->num != other.num;
}

template<uint32_t _base>
bool Ring<_base>::operator>(const Ring<_base>& other)const
{
	return this->num == other.num;
}

template<uint32_t _base>
bool Ring<_base>::operator<(const Ring<_base>& other)const
{
	return this->num != other.num;
}

#endif 