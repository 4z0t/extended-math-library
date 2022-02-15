#ifndef Ring_H
#define Ring_H
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <concepts>
#define NOT_PRIME_NUMBER_ERROR -1

//static constexpr bool _is_prime(uint32_t _base)
//{
//	for (uint32_t i = 2; i <= (uint32_t)sqrt(_base); i++)
//		if (_base % i == 0)
//			return false;
//	if (_base == 0 || _base == 1)
//		return false;
//	return true;
//}
constexpr bool _is_prime(std::size_t N, std::size_t I = 2) {
	return (N != 2 ? N % I : true) //make 2 prime and check divisibility if not 2
		&& (N >= 2) //0 and 1 are not prime
		&& (I >= N - 1 ? true : _is_prime(N, I + 1)); //stop when I is too big
}

//template <uint32_t _base, uint32_t val>struct is_prime_val
//{
//	static constexpr const bool  value{ (val == 0) ? true : (_base == 1 || _base == 0) ? false : (_base % val != 0) && is_prime_val<_base,val - 1>::value };
//};
//template <uint32_t _base> struct is_prime {
//	static constexpr const bool  value{ is_prime_val<_base,_base>::value};
//};
template <uint32_t _base> struct is_prime {
	static constexpr const bool  value{ _is_prime(_base) };
};
template<uint32_t _base>
concept Is_prime = _is_prime(_base);

template<uint32_t _base>
requires  Is_prime<_base>
class Ring
{
	int32_t num;
	static  const int* reciprocals;
	static bool checked;
	static uint32_t total_objects;
	/*void prime_exit(const uint32_t& num)
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
	}*/

	void fillreciprocals()
	{

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
static constexpr const int* calcreciprocals(uint32_t _base)
{
	int* reciprocals = new int[_base] {};
	reciprocals[1] = 1;
	for (uint32_t i = 2; i < _base; i++)
		reciprocals[i] = (_base - (_base / i) * reciprocals[_base % i] % _base) % _base;
	return reciprocals;
}

//template <uint32_t _base>
//void constexpr fillreciprocals(int reciprocals[_base])
//{
//
//	reciprocals = new int[_base] {};
//	reciprocals[1] = 1;
//	for (uint32_t i = 2; i < _base; i++)
//		reciprocals[i] = (_base - (_base / i) * reciprocals[_base % i] % _base) % _base;
//
//}





template<uint32_t _base>
requires Is_prime<_base>
 const int* Ring<_base>::reciprocals = calcreciprocals(_base);



template<uint32_t _base>
requires Is_prime<_base>
uint32_t Ring<_base> ::total_objects = 0;

template<uint32_t _base>
requires Is_prime<_base>
bool  Ring<_base>::checked = false;


template<uint32_t _base>
requires Is_prime<_base>
Ring<_base>::Ring()
{
	//this->prime_exit(_base);
	this->fillreciprocals();
	this->num = 0;
	this->total_objects++;
}

template<uint32_t _base>
requires Is_prime<_base>
Ring<_base>::Ring(const Ring<_base>& other)
{
	this->num = other.num;
	this->total_objects++;
}

template<uint32_t _base>
requires Is_prime<_base>
Ring<_base>::Ring(const int32_t& value)
{
	//this->prime_exit(_base);
	this->fillreciprocals();
	if (value >= 0)
		this->num = value % (int32_t)_base;
	else
		this->num = (value % (int32_t)_base) + _base;
	this->total_objects++;
}

template<uint32_t _base>
requires Is_prime<_base>
Ring<_base>::Ring(const uint32_t& value)
{
	//this->prime_exit(_base);
	this->fillreciprocals();
	this->num = value % _base;
	this->total_objects++;
}



template<uint32_t _base>
requires Is_prime<_base>
Ring<_base>::~Ring()
{
	this->total_objects--;
	if (this->total_objects == 0)
	{
		delete[]this->reciprocals;
		//this->reciprocals = nullptr;
		//#ifdef _IOSTREAM_
		//		std::cout << "memory cleared for " << _base << std::endl;
		//#endif
	}
}

// overriding compare operators for standart numerics
template<class U, uint32_t _base>
requires Is_prime<_base>
Ring<_base> operator==(const U& value, const Ring<_base>& other)
{
	return Ring<_base>(value) == other;
}

template<class U, uint32_t _base>
requires Is_prime<_base>
Ring<_base> operator!=(const U& value, const Ring<_base>& other)
{
	return Ring<_base>(value) != other;
}

template<class U, uint32_t _base>
requires Is_prime<_base>
Ring<_base> operator>(const U& value, const Ring<_base>& other)
{
	return Ring<_base>(value) > other;
}

template<class U, uint32_t _base>
requires Is_prime<_base>
Ring<_base> operator<(const U& value, const Ring<_base>& other)
{
	return Ring<_base>(value) < other;
}

template<class U, uint32_t _base>
requires Is_prime<_base>
Ring<_base> operator>=(const U& value, const Ring<_base>& other)
{
	return Ring<_base>(value) >= other;
}

template<class U, uint32_t _base>
requires Is_prime<_base>
Ring<_base> operator<=(const U& value, const Ring<_base>& other)
{
	return Ring<_base>(value) <= other;
}
//



// overriding operators for standart numerics
template<class U, uint32_t _base>
requires Is_prime<_base>
Ring<_base> operator/(const U& value, const Ring<_base>& other)
{
	return Ring<_base>(value) / other;
}

template<class U, uint32_t _base>
requires Is_prime<_base>
Ring<_base> operator*(const U& value, const Ring<_base>& other)
{
	return Ring<_base>(value) * other;
}

template<class U, uint32_t _base>
requires Is_prime<_base>
Ring<_base> operator+(const U& value, const Ring<_base>& other)
{
	return Ring<_base>(value) + other;
}

template<class U, uint32_t _base>
requires Is_prime<_base>
Ring<_base> operator-(const U& value, const Ring<_base>& other)
{
	return Ring<_base>(value) - other;
}



template<uint32_t _base>
requires Is_prime<_base>
Ring<_base>& Ring<_base>::operator=(const Ring<_base>& other)
{
	this->num = other.num;
	return *this;
}

template<uint32_t _base>
requires Is_prime<_base>
Ring<_base> Ring<_base>::operator-() const
{
	if (this->num == 0)
		return 0;
	Ring<_base> result;
	result.num = _base - this->num;
	return result;
}

template<uint32_t _base>
requires Is_prime<_base>
Ring<_base> Ring<_base>::operator+(const Ring<_base>& other) const
{
	Ring<_base> result;
	result.num = (this->num + other.num) % _base;
	return result;
}

template<uint32_t _base>
requires Is_prime<_base>
Ring<_base> Ring<_base>::operator-(const Ring<_base>& other) const
{
	return *this + (-other);
}

template<uint32_t _base>
requires Is_prime<_base>
Ring<_base> Ring<_base>::operator*(const Ring<_base>& other) const
{
	Ring<_base> result;
	result.num = (this->num * other.num) % _base;
	return result;
}

template<uint32_t _base>
requires Is_prime<_base>
Ring<_base> Ring<_base>::operator/(const Ring<_base>& other) const
{
	if (other == 0)
		throw "zero division error";
	Ring<_base> result;
	result.num = (this->num * this->reciprocals[other.num]) % _base;
	return result;
}

template<uint32_t _base>
requires Is_prime<_base>
Ring<_base> Ring<_base>::operator~() const
{
	Ring<_base> result;
	result.num = this->reciprocals[this->num];
	return result;
}

template<uint32_t _base>
requires Is_prime<_base>
Ring<_base> reciprocal(const Ring<_base>& value)
{
	Ring<_base> result;
	result.num = value.reciprocals[value.num];
	return result;
}


template<uint32_t _base>
requires Is_prime<_base>
Ring<_base>& Ring<_base>::operator/=(const Ring<_base>& other)
{
	return *this = *this / other;
}

template<uint32_t _base>
requires Is_prime<_base>
Ring<_base>& Ring<_base>::operator*=(const Ring<_base>& other)
{
	return *this = *this * other;
}

template<uint32_t _base>
requires Is_prime<_base>
Ring<_base>& Ring<_base>::operator-=(const Ring<_base>& other)
{
	return *this = *this - other;
}

template<uint32_t _base>
requires Is_prime<_base>
Ring<_base>& Ring<_base>::operator+=(const Ring<_base>& other)
{
	return *this = *this + other;
}

template<uint32_t _base>
requires Is_prime<_base>
bool Ring<_base>::operator==(const Ring<_base>& other)const
{
	return this->num == other.num;
}

template<uint32_t _base>
requires Is_prime<_base>
bool Ring<_base>::operator!=(const Ring<_base>& other)const
{
	return this->num != other.num;
}

template<uint32_t _base>
requires Is_prime<_base>
bool Ring<_base>::operator>=(const Ring<_base>& other)const
{
	return this->num == other.num;
}

template<uint32_t _base>
requires Is_prime<_base>
bool Ring<_base>::operator<=(const Ring<_base>& other)const
{
	return this->num != other.num;
}

template<uint32_t _base>
requires Is_prime<_base>
bool Ring<_base>::operator>(const Ring<_base>& other)const
{
	return this->num == other.num;
}

template<uint32_t _base>
requires Is_prime<_base>
bool Ring<_base>::operator<(const Ring<_base>& other)const
{
	return this->num != other.num;
}

#endif 