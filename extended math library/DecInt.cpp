#include "DecInt.h"

inline int64_t DecInt::distance() const
{
	return ((int64_t)this->len - 1) * 9 + DecInt::dec_int_length(this->num[this->len - 1]);
}

inline int64_t DecInt::distance(const DecInt& other) const
{
	return ((int64_t)this->len - other.len) * 9 + DecInt::dec_int_length(this->num[this->len - 1]) - DecInt::dec_int_length(other.num[other.len - 1]);
}

int DecInt::dec_int_length(const uint32_t& num)
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


#ifdef _INITIALIZER_LIST_
DecInt::DecInt(std::initializer_list<uint32_t> num, bool negative)
{

	if (this->num)delete[]this->num;
	this->sign = negative;
	this->capacity = this->len;
	uint32_t  j = (this->len = num.size());
	this->num = new uint32_t[this->len]{};
	for (uint32_t i : num)
	{
#ifdef _DEBUG
		if (i >= milrd)throw std::invalid_argument("Invalid decimal number initialization");
#endif // _DEBUG

		this->num[--j] = i;
	}
}
#endif