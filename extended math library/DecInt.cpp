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

DecInt::DecInt(const DecInt& other) :DecInt(other.capacity, other.sign)
{
	this->len = other.len;
	for (uint32_t i = 0; i < this->len; i++)
		this->num[i] = other.num[i];
}


