#pragma once
#include <stdint.h>
#include <stdexcept>
#ifndef INTBASE_H
#define INTBASE_H

template <typename T>
class IntBase
{
public:

	static constexpr int GREATER = 1;
	static constexpr int EQUAL = 0;
	static constexpr int LESS = -1;

protected:
	uint32_t* _num = nullptr;
	uint32_t _capacity = 0;
	uint32_t _len = 0;
	bool _sign = false;


	void extend(const uint32_t& cap);

	T& normalize();

	T& cut_zeros();

	T movecells(const uint32_t& shift)const;
	T& movethiscells(const uint32_t& shift);

	T cut(const uint32_t& length)const;
	T& cutthis(const uint32_t& length);

	int abs_compare(const IntBase& other)const;

	virtual int64_t distance()const = 0;
	virtual int64_t distance(const T&)const = 0;
	IntBase(const uint32_t& capacity, bool sign);
public:







	bool operator==(const IntBase& other)const;
	bool operator!=(const IntBase& other)const;
	bool operator>(const IntBase& other)const;
	bool operator>=(const IntBase& other)const;
	bool operator<(const IntBase& other)const;
	bool operator<=(const IntBase& other)const;

	bool zero()const;

	explicit operator bool()const;


	virtual T operator*(const T& other)const = 0;
	virtual T operator+(const T& other)const = 0;
	virtual T operator-(const T& other)const = 0;
	virtual T operator/(const T& other)const = 0;
	virtual T operator%(const T& other)const = 0;

	virtual T& operator=(const T& other) = 0;

	virtual T& operator*=(const T& other) = 0;
	virtual T& operator+=(const T& other) = 0;
	virtual T& operator-=(const T& other) = 0;
	virtual T& operator/=(const T& other) = 0;
	virtual T& operator%=(const T& other) = 0;

	virtual T& operator++() = 0;
	virtual T operator++(int) = 0;
	virtual T& operator--() = 0;
	virtual T operator--(int) = 0;
	virtual T operator-()const = 0;



	IntBase();
	IntBase(const IntBase& other);

#ifdef _DEBUG 
#ifdef _IOSTREAM_
	void debug_log()
	{
		std::cout << "len: " << this->_len << '\n'
			<< "cap: " << this->_capacity << '\n';
		for (int i = 0; i < this->_capacity; i++)
		{
			std::cout << i << ":\t" << this->_num[i] << '\n';
		}
	}
#endif
#endif // _DEBUG


	~IntBase();
};


template<typename T>
bool IntBase<T>:: operator==(const IntBase& other)const
{
	return  (this->_sign == other._sign) && (EQUAL == this->abs_compare(other));
}

template<typename T>
bool IntBase<T>::operator!=(const IntBase& other)const
{
	return !(*this == other);
}

template<typename T>
bool IntBase<T>::operator>(const IntBase& other)const
{
	if (!this->_sign && other._sign)
		return true;
	if (this->_sign && !other._sign)
		return false;
	return (!(this->_sign && other._sign)) == (this->abs_compare(other) == GREATER);
}

template<typename T>
bool IntBase<T>::operator>=(const IntBase& other)const
{
	return (*this == other) || (*this > other);
}

template<typename T>
bool IntBase<T>:: operator<(const IntBase& other)const
{
	return !(*this >= other);
}

template<typename T>
bool IntBase<T>::operator<=(const IntBase& other)const
{
	return !(*this > other);
}




template<typename T>
void IntBase<T>::extend(const uint32_t& cap)
{
#ifdef _DEBUG
	if (cap <= this->_capacity)throw std::invalid_argument("New capacity cant be less than current one");
#endif // DEBUG
	uint32_t* new_num = new uint32_t[cap]{};
	for (uint32_t i = 0; i < this->_len; i++)
		new_num[i] = this->_num[i];
	delete[] this->_num;
	this->_capacity = cap;
	this->_num = new_num;
}
template<typename T>
bool IntBase<T>::zero() const
{
	return this->_num[this->_len - 1] == 0;
}
template<typename T>
inline IntBase<T>::operator bool() const
{
	return !this->zero();
}
template<typename T>
inline T& IntBase<T>::normalize()
{
	this->cut_zeros();
	if (this->zero())this->_sign = false;
	return *(T*)this;
}
template<typename T>
T& IntBase<T>::cut_zeros()
{
	if (this->_num[this->_len - 1] == 0)
		for (uint32_t i = this->_len - 1; ; i--)
			if (this->_num[i] != 0 || i == 0)
			{
				this->_len = i + 1;
				break;
			}
	return *(T*)this;
}

template<typename T>
T IntBase<T>::movecells(const uint32_t& shift) const
{
	if (shift)
	{
		T new_int(this->_len + shift, this->_sign);
		for (uint32_t i = 0; i < this->_len; i++)
			new_int._num[i + shift] = this->_num[i];
		return new_int;
	}
	return *(T*)this;
}

template<typename T>
T& IntBase<T>::movethiscells(const uint32_t& shift)
{
	if (shift)
	{
		if (shift + this->_len > this->_capacity)
		{
			uint32_t* new_num = new  uint32_t[this->_len + shift]{};
			for (uint32_t i = 0; i < this->_len; i++)
				new_num[i + shift] = this->_num[i];
			delete[] this->_num;
			this->_len += shift;
			this->_capacity = this->_len;
			this->_num = new_num;
		}
		else
		{
			for (uint32_t i = this->_len + shift - 1; i >= shift; i--)
				this->_num[i] = this->_num[i - shift];
			for (uint32_t i = 0; i < shift; i++)
				this->_num[i] = 0;
			this->_len += shift;
		}
	}
	return *(T*)this;
}

template<typename T>
T IntBase<T>::cut(const uint32_t& length) const
{
	if (this->_len > length)
	{
		T new_unlint(this->_len - length, this->_sign);
		for (uint32_t i = 0; i < new_unlint._len; i++)
		{
			new_unlint._num[i] = this->_num[i + length];
		}
		return new_unlint;
	}
	return T();
}

template<typename T>
T& IntBase<T>::cutthis(const uint32_t& length)
{
	if (this->_len > length)
	{
		uint32_t* new_num = new uint32_t[this->_len -= length]{};
		for (uint32_t i = 0; i < this->_len; i++)
		{
			new_num[i] = this->_num[i + length];
		}
		delete[] this->_num;
		this->_num = new_num;
		this->_capacity = this->_len;
		return *(T*)this;
	}
	delete[] this->_num;
	this->_num = new uint32_t[this->_len = 1]{};
	this->_capacity = 1;
	return *(T*)this;
}

template<typename T>
int IntBase<T>::abs_compare(const IntBase& other)const
{
	if (this->_len > other._len)
		return GREATER;
	if (this->_len < other._len)
		return LESS;
	for (uint32_t i = this->_len - 1; ; i--)
	{
		if (this->_num[i] != other._num[i])
			return  (this->_num[i] > other._num[i]) ? GREATER : LESS;
		if (i == 0)
			return EQUAL;
	}
}

template<typename T>
IntBase<T>::IntBase()
{
	this->_sign = false;
	this->_len = 1;
	this->_capacity = 1;
	this->_num = new uint32_t[this->_capacity]{};
}

template<typename T>
IntBase<T>::IntBase(const uint32_t& capacity, bool sign)
{
	this->_sign = sign;
	this->_len = capacity;
	this->_capacity = capacity;
	this->_num = new uint32_t[this->_capacity]{};
}

template<typename T>
IntBase<T>::IntBase(const IntBase& other) : IntBase(other._len, other._sign)
{
	for (uint32_t i = 0; i < this->_len; i++)
		this->_num[i] = other._num[i];
}

template<typename T>
IntBase<T>::~IntBase()
{

#ifdef _DEBUG
	if (_num)
#endif // DEBUG
		delete[]_num;
}


#endif