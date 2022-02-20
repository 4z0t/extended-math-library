#include "DecInt.h"
#ifndef _EMLIO_
#define _EMLIO_
#ifdef _IOSTREAM_
#ifdef DECINT_H





void DecInt::print(bool sep = false) const
{
	bool zeros = true;
	if (this->_sign)
		std::cout << '-';
	for (uint32_t i = this->_len - 1; ; i--)
	{
		for (int j = 0; j < 9 - DecInt::dec_int_length(this->_num[i]) && !zeros; j++)
			std::cout << 0;
		if (this->_num[i] != 0 || (i == 0 && zeros))
		{
			std::cout << this->_num[i];
		}

		zeros = ((this->_num[i] == 0) && zeros);
		if (i == 0)break;
		if (sep)std::cout << '\'';
	}
	std::cout << std::endl;
}



std::ostream& operator<<(std::ostream& os, const DecInt& value)
{
	bool zeros = true;
	if (value._sign)
		os << '-';
	for (uint32_t i = value._len - 1; ; i--)
	{
		for (int j = 0; j < 9 - DecInt::dec_int_length(value._num[i]) && !zeros; j++)
			os << 0;
		if (value._num[i] != 0 || (i == 0 && zeros))
			os << value._num[i];
		zeros = ((value._num[i] == 0) && zeros);
		if (i == 0)break;
	}
	return os;
}

#endif // DEBUG
#endif
#endif