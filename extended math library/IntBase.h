#pragma once
#include <stdint.h>
#include <stdexcept>
#ifndef INTBASE_H
#define INTBASE_H

template <typename T>
class IntBase
{
protected: 
	uint32_t* num = nullptr;
	uint32_t capacity = 0;
	uint32_t len = 0;
	bool sign = false;


	void extend(const uint32_t& cap);
	T& cut_zeros();

	T movecells(const uint32_t& shift)const;
	T& movethiscells(const uint32_t& shift);

	T cut(const uint32_t& length)const;
	T& cutthis(const uint32_t& length);

public:
	IntBase();
	IntBase(const uint32_t& capacity, bool sign);
	IntBase(const IntBase& other);
	~IntBase();
};







template<typename T>
void IntBase<T>::extend(const uint32_t& cap)
{
#ifdef _DEBUG
	if (cap <= this->capacity)throw std::invalid_argument("New capacity cant be less than current one");
#endif // DEBUG
	uint32_t* new_num = new uint32_t[cap]{};
	for (uint32_t i = 0; i < this->len; i++)
		new_num[i] = this->num[i];
	delete[] this->num;
	this->capacity = cap;
	this->num = new_num;
}
template<typename T>
T& IntBase<T>::cut_zeros()
{
	if (this->num[this->len - 1] == 0)
		for (uint32_t i = this->len - 1; ; i--)
			if (this->num[i] != 0 || i == 0)
			{
				this->len = i + 1;
				return *this;
			}
	return *(T*)this;
}

template<typename T>
T IntBase<T>::movecells(const uint32_t& shift) const
{
	if (shift)
	{
		T new_int(this->len + shift, this->sign);
		for (uint32_t i = 0; i < this->len; i++)
			new_int.num[i + shift] = this->num[i];
		return new_int;
	}
	return *(T*)this;
}

template<typename T>
T& IntBase<T>::movethiscells(const uint32_t& shift)
{
	if (shift)
	{
		if (shift + this->len > this->capacity)
		{
			uint32_t* new_num = new  uint32_t[this->len + shift]{};
			for (uint32_t i = 0; i < this->len; i++)
				new_num[i + shift] = this->num[i];
			delete[] this->num;
			this->len += shift;
			this->capacity = this->len;
			this->num = new_num;
		}
		else
		{
			for (uint32_t i = this->len + shift - 1; i >= shift; i--)
				this->num[i] = this->num[i - shift];
			for (uint32_t i = 0; i < shift; i++)
				this->num[i] = 0;
			this->len += shift;
		}
	}
	return *(T*)this;
}

template<typename T>
T IntBase<T>::cut(const uint32_t& length) const
{
	if (this->len > length)
	{
		T new_unlint(this->len - length, this->sign);
		for (uint32_t i = 0; i < new_unlint.len; i++)
		{
			new_unlint.num[i] = this->num[i + length];
		}
		return new_unlint;
	}
	return T();
}

template<typename T>
T& IntBase<T>::cutthis(const uint32_t& length)
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
		this->capacity = this->len;
		return *(T*)this;
	}
	delete[] this->num;
	this->num = new uint32_t[this->len = 1]{};
	this->capacity = 1;
	return *(T*)this;
}

template<typename T>
IntBase<T>::IntBase()
{
	this->sign = false;
	this->len = 1;
	this->capacity = 1;
	this->num = new uint32_t[this->capacity]{};
}

template<typename T>
IntBase<T>::IntBase(const uint32_t& capacity, bool sign)
{
	this->sign = sign;
	this->len = capacity;
	this->capacity = capacity;
	this->num = new uint32_t[this->capacity]{};
}

template<typename T>
IntBase<T>::IntBase(const IntBase& other): IntBase(other.len, other.sign)
{
	for (uint32_t i = 0; i < this->len; i++)
		this->num[i] = other.num[i];
}

template<typename T>
IntBase<T>::~IntBase()
{
	if (num)delete[]num;
}


#endif