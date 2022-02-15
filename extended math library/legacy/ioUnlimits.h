
#ifndef _IOUNLIMITS_
#define _IOUNLIMITS_
#ifdef _IOSTREAM_
#ifdef UNLINT_H
void Unlint::print()const
{
	bool zeros = true;
	if (this->negative)
		std::cout << '-';
	for (uint32_t i = this->len - 1; ; i--)
	{
		for (int j = 0; j < 9 - length_int(this->num[i]) && !zeros; j++)
			std::cout << 0;
		if (this->num[i] != 0 || (i == 0 && zeros))
			std::cout << this->num[i];
		zeros = ((this->num[i] == 0) && zeros);
		if (i == 0)break;
	}
	std::cout << std::endl;
}
std::ostream& operator<<(std::ostream& os, const Unlint& value)
{
	bool zeros = true;
	if (value.negative)
		os << '-';
	for (uint32_t i = value.len - 1; ; i--)
	{
		for (int j = 0; j < 9 - length_int(value.num[i]) && !zeros; j++)
			os << 0;
		if (value.num[i] != 0 || (i == 0 && zeros))
			os << value.num[i];
		zeros = ((value.num[i] == 0) && zeros);
		if (i == 0)break;
	}
	return os;
}
#endif
#ifdef UNREAL_H
std::ostream& operator<<(std::ostream& os, const Unreal& value)
{
	if (value.precision >= value.number.len)
	{
		uint32_t zero_counter = (value.precision - value.number.len);
		if (value.number.negative)
			os << '-';
		os << "0.";
		for (uint32_t i = value.number.len - 1; ; i--)
		{
			if (value.number.num[i] == 0)
				zero_counter++;
			else
			{
				for (uint32_t zeros = 0; zeros < zero_counter * 9; zeros++)
					os << 0;
				for (uint32_t j = 0; j < 9 - length_int(value.number.num[i]); j++)
					os << 0;
				if (value.number.num[i] != 0)
					os << value.number.num[i];
				zero_counter = 0;
			}
			if (i == 0)break;
		}
	}
	else
	{
		bool zeros = true;
		if (value.number.negative)
			os << '-';
		for (uint32_t i = value.number.len - 1; i >= value.precision; i--)
		{
			for (uint32_t j = 0; j < 9 - length_int(value.number.num[i]) && !zeros; j++)
				os << 0;
			if (value.number.num[i] != 0 || (i == 0 && zeros))
				os << value.number.num[i];
			zeros = ((value.number.num[i] == 0) && zeros);
		}
		uint32_t zero_counter = 0;
		os << '.';
		for (int i = value.precision - 1; i >= 0; i--)
		{
			if (value.number.num[i] == 0)
				zero_counter++;
			else
			{
				for (uint32_t zeros = 0; zeros < zero_counter * 9; zeros++)
					os << 0;
				for (uint32_t j = 0; j < 9 - length_int(value.number.num[i]); j++)
					os << 0;
				if (value.number.num[i] != 0)
					os << value.number.num[i];
				zero_counter = 0;
			}
		}
	}
	return os;
}
void Unreal::print()const
{
	if (this->precision >= this->number.len)
	{
		uint32_t zero_counter = (this->precision - this->number.len);
		if (this->number.negative)
			std::cout << '-';
		std::cout << "0.";

		for (uint32_t i = this->number.len - 1; ; i--)
		{
			if (this->number.num[i] == 0)
				zero_counter++;
			else
			{
				for (uint32_t zeros = 0; zeros < zero_counter * 9; zeros++)
					std::cout << 0;
				for (uint32_t j = 0; j < 9 - length_int(this->number.num[i]); j++)
					std::cout << 0;
				if (this->number.num[i] != 0)
					std::cout << this->number.num[i];
				zero_counter = 0;
			}
			if (i == 0)break;
		}
		std::cout << std::endl;
	}
	else
	{
		bool zeros = true;
		if (this->number.negative)
			std::cout << '-';
		for (uint32_t i = this->number.len - 1; i >= this->precision; i--)
		{
			for (uint32_t j = 0; j < 9 - length_int(this->number.num[i]) && !zeros; j++)
				std::cout << 0;
			if (this->number.num[i] != 0 || (i == 0 && zeros))
				std::cout << this->number.num[i];
			zeros = ((this->number.num[i] == 0) && zeros);
		}
		uint32_t zero_counter = 0;
		std::cout << '.';
		for (int i = this->precision - 1; i >= 0; i--)
		{
			if (this->number.num[i] == 0)
				zero_counter++;
			else
			{
				for (uint32_t zeros = 0; zeros < zero_counter * 9; zeros++)
					std::cout << 0;
				for (uint32_t j = 0; j < 9 - length_int(this->number.num[i]); j++)
					std::cout << 0;
				if (this->number.num[i] != 0)
					std::cout << this->number.num[i];
				zero_counter = 0;
			}
		}
		std::cout << std::endl;
	}
}
#endif
#endif


#ifdef _FSTREAM_
#ifdef UNLINT_H
Unlint::Unlint(std::string filename)
{
	this->readbytesfromfile(filename);
}

void Unlint::printinfile(std::string filename)
{
	std::ofstream outfile;
	outfile.open(filename);
	if (!outfile.is_open())exit(CANT_OPEN_FILE);
	bool zeros = true;
	if (this->negative)
		outfile << '-';
	for (uint32_t i = this->len - 1;; i--)
	{
		for (uint32_t j = 0; j < 9 - length_int(this->num[i]) && !zeros; j++)
			outfile << 0;
		if (this->num[i] != 0 || (i == 0 && zeros))
			outfile << this->num[i];
		zeros = ((this->num[i] == 0) && zeros);
		if (i == 0)break;
	}
	outfile << std::endl;
	outfile.close();
}
void Unlint::readbytesfromfile(std::string filename)
{
	std::ifstream infile;
	infile.open(filename, std::ios_base::in | std::ios_base::binary);
	if (!infile.is_open())exit(CANT_OPEN_FILE);
	if (this->num != nullptr)delete[] this->num;
	infile.read((char*)&this->negative, sizeof(bool));
	infile.read((char*)&this->len, sizeof(uint32_t));
	this->num = new uint32_t[this->len]{};
	for (uint32_t i = 0; i < this->len; i++)
		infile.read((char*)&this->num[i], sizeof(uint32_t));
	infile.close();
}

void Unlint::writebytestofile(std::string filename)
{
	std::ofstream outfile;
	outfile.open(filename, std::ios_base::out | std::ios_base::binary);
	if (!outfile.is_open())exit(CANT_OPEN_FILE);
	char* byte = bytes(*this);
	outfile.write(byte, this->getsize());
	delete[] byte;
	outfile.close();
}

void Unlint::writebytestofile(std::string filename)const
{
	std::ofstream outfile;
	outfile.open(filename, std::ios_base::out | std::ios_base::binary);
	if (!outfile.is_open())exit(CANT_OPEN_FILE);
	char* byte = bytes(*this);
	outfile.write(byte, this->getsize());
	delete[] byte;
	outfile.close();
}
#endif

#ifdef UNREAL_H

Unreal::Unreal(std::string filename)
{
	this->readbytesfromfile(filename);
}


void Unreal::printinfile(std::string filename)
{
	std::ofstream outfile;
	outfile.open(filename);
	if (!outfile.is_open())exit(CANT_OPEN_FILE);
	if (this->precision >= this->number.len)
	{
		uint32_t zero_counter = (this->precision - this->number.len);
		if (this->number.negative)
			outfile << '-';
		outfile << "0.";

		for (uint32_t i = this->number.len - 1; ; i--)
		{
			if (this->number.num[i] == 0)
				zero_counter++;
			else
			{
				for (uint32_t zeros = 0; zeros < zero_counter * 9; zeros++)
					outfile << 0;
				for (uint32_t j = 0; j < 9 - length_int(this->number.num[i]); j++)
					outfile << 0;
				if (this->number.num[i] != 0)
					outfile << this->number.num[i];
				zero_counter = 0;
			}
			if (i == 0)break;
		}
		outfile << std::endl;
	}
	else
	{
		bool zeros = true;
		if (this->number.negative)
			outfile << '-';
		for (uint32_t i = this->number.len - 1; i >= this->precision; i--)
		{
			for (uint32_t j = 0; j < 9 - length_int(this->number.num[i]) && !zeros; j++)
				outfile << 0;
			if (this->number.num[i] != 0 || (i == 0 && zeros))
				outfile << this->number.num[i];
			zeros = ((this->number.num[i] == 0) && zeros);
		}


		uint32_t zero_counter = 0;
		outfile << '.';
		for (int i = this->precision - 1; i >= 0; i--)
		{
			if (this->number.num[i] == 0)
				zero_counter++;
			else
			{
				for (uint32_t zeros = 0; zeros < zero_counter * 9; zeros++)
					outfile << 0;
				for (uint32_t j = 0; j < 9 - length_int(this->number.num[i]); j++)
					outfile << 0;
				if (this->number.num[i] != 0)
					outfile << this->number.num[i];
				zero_counter = 0;
			}
		}
		outfile << std::endl;
		outfile.close();
	}
}

void Unreal::readbytesfromfile(std::string filename)
{
	std::ifstream infile;
	infile.open(filename, std::ios_base::in | std::ios_base::binary);
	if (!infile.is_open())exit(CANT_OPEN_FILE);
	if (this->number.num != nullptr)delete[] this->number.num;
	infile.read((char*)&this->number.negative, sizeof(bool));
	infile.read((char*)&this->number.len, sizeof(uint32_t));
	this->number.num = new uint32_t[this->number.len]{};
	for (uint32_t i = 0; i < this->number.len; i++)
		infile.read((char*)&this->number.num[i], sizeof(uint32_t));
	infile.read((char*)&this->precision, sizeof(uint32_t));
	infile.close();
}

void Unreal::writebytestofile(std::string filename)
{
	std::ofstream outfile;
	outfile.open(filename, std::ios_base::out | std::ios_base::binary);
	if (!outfile.is_open())exit(CANT_OPEN_FILE);
	char* byte = bytes(this->number);
	outfile.write(byte, this->number.getsize());
	outfile.write((char*)&this->precision, sizeof(uint32_t));
	delete[] byte;
	outfile.close();
}

void Unreal::writebytestofile(std::string filename)const
{
	std::ofstream outfile;
	outfile.open(filename, std::ios_base::out | std::ios_base::binary);
	if (!outfile.is_open())exit(CANT_OPEN_FILE);
	char* byte = bytes(this->number);
	outfile.write(byte, this->number.getsize());
	outfile.write((char*)&this->precision, sizeof(uint32_t));
	delete[] byte;
	outfile.close();
}
#endif
#endif
#endif