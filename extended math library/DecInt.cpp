#include "DecInt.h"

inline int64_t DecInt::distance() const
{
	return ((int64_t)this->_len - 1) * 9 + DecInt::dec_int_length(this->_num[this->_len - 1]);
}

inline int64_t DecInt::distance(const DecInt& other) const
{
	return ((int64_t)this->_len - other._len) * 9 + DecInt::dec_int_length(this->_num[this->_len - 1]) - DecInt::dec_int_length(other._num[other._len - 1]);
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

	if (this->_num)delete[]this->_num;
	this->_sign = negative;
	uint32_t  j = (this->_len = num.size());
	this->_capacity = this->_len;
	this->_num = new uint32_t[this->_len]{};
	for (uint32_t i : num)
	{
#ifdef _DEBUG
		if (i >= milrd)throw std::invalid_argument("Invalid decimal number initialization");
#endif // _DEBUG

		this->_num[--j] = i;
	}
	this->cut_zeros(); 
}
#endif