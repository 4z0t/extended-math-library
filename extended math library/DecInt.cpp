#include "DecInt.h"

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