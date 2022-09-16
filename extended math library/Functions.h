#pragma once
#ifdef DECINT_H

DecInt dec_factorial(const u32& val)
{
	DecInt result = 1;
	for (u32 i = 2; i <= val; i++)
		result *= i;
	return result;
}

DecInt dec_fib(const u32& val)
{
	DecInt result = 0;
	DecInt a = 1;
	DecInt b = 1;
	for (u32 i = 0; i < val; i++)
	{
		b = a + result;
		result = a;
		a = b;
	}
	return result;
}
#endif // DECINT_H

#ifdef BININT_H
BinInt bin_factorial(const u32& val)
{
	BinInt result = 1;
	for (u32 i = 2; i <= val; i++)
		result *= i;
	return result;
}

BinInt bin_fib(const u32& val)
{
	BinInt result = 0;
	BinInt a = 1;
	BinInt b = 1;
	for (u32 i = 0; i < val; i++)
	{
		b = a + result;
		result = a;
		a = b;
	}
	return result;
}

#endif // BININT_H
