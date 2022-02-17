#pragma once
#include <stdint.h>
#include <stdexcept>

template <typename T>
class IntBase
{
protected:

	uint32_t* num = nullptr;
	uint32_t capacity = 0;
	uint32_t len = 0;
	bool sign = false;


	void extend(const uint32_t& cap)
	{
#ifdef DEBUG
		if (cap < this->capacity)throw std::invalid_argument("New capacity cant be more than current one");
#endif // DEBUG
		uint32_t* new_num = new uint32_t[cap]{};
		for (uint32_t i = 0; i < this->len; i++)
			new_num[i] = this->num[i];
		delete[] this->num;
		this->capacity = cap;
		this->num = new_num;
	}

	T& cut_zeros()
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


	//>???????????
	/*T movecells(const uint32_t& length)const
	{
		if (length)
		{
			T new_unlint(this->len + length, this->negative);
			for (uint32_t i = 0; i < this->len; i++)
				new_unlint.num[i + length] = this->num[i];
			return new_unlint;
		}
		return *this;
	}

	T& movethiscells(const uint32_t& length)
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
	}*/



public:
	IntBase() {
	};
	IntBase(const IntBase& other) = delete;
	~IntBase() {
		if (num)delete[]num;
	}
};

