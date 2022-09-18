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
#ifdef FLOAT_BASE_H

std::ostream& operator<<(std::ostream& os, const FloatBase<DecInt>& value)
{
	if (value._precision >= value._int._len)
	{
		uint32_t zero_counter = (value.precision - value._int.len);
		if (value._int.negative)
			os << '-';
		os << "0.";
		for (uint32_t i = value._int.len - 1; ; i--)
		{
			if (value._int.num[i] == 0)
				zero_counter++;
			else
			{
				for (uint32_t zeros = 0; zeros < zero_counter * 9; zeros++)
					os << 0;
				for (uint32_t j = 0; j < 9 - length_int(value._int.num[i]); j++)
					os << 0;
				if (value._int.num[i] != 0)
					os << value._int.num[i];
				zero_counter = 0;
			}
			if (i == 0)break;
		}
	}
	else
	{
		bool zeros = true;
		if (value._int.negative)
			os << '-';
		for (uint32_t i = value._int.len - 1; i >= value.precision; i--)
		{
			for (uint32_t j = 0; j < 9 - length_int(value._int.num[i]) && !zeros; j++)
				os << 0;
			if (value._int.num[i] != 0 || (i == 0 && zeros))
				os << value._int.num[i];
			zeros = ((value._int.num[i] == 0) && zeros);
		}
		uint32_t zero_counter = 0;
		os << '.';
		for (int i = value.precision - 1; i >= 0; i--)
		{
			if (value._int.num[i] == 0)
				zero_counter++;
			else
			{
				for (uint32_t zeros = 0; zeros < zero_counter * 9; zeros++)
					os << 0;
				for (uint32_t j = 0; j < 9 - length_int(value._int.num[i]); j++)
					os << 0;
				if (value._int.num[i] != 0)
					os << value._int.num[i];
				zero_counter = 0;
			}
		}
	}
	return os;
}
#endif // FLOAT_BASE_H
#endif //DECINT_H

#ifdef BININT_H
void BinInt::print(bool sep) const
{
}

std::ostream& operator<<(std::ostream& os, const BinInt& value)
{

	if (value._sign)
		os << '-';
	os << std::hex;
	for (u32 i = value._len - 1;; i--)
	{
		os.fill('0');
		os.width(8);
		os << value._num[i] << '.';
		if (i == 0)break;
	}
	os << std::dec << std::endl;
	return os;
}

#endif //BININT_H


#endif //_IOSTREAM_
#endif//_EMLIO_