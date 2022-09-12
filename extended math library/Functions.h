#pragma once
#ifdef DECINT_H

DecInt factorial(const u32& val)
{
	DecInt result = 1;
	for (u32 i = 2; i <= val; i++)
		result *= i;
	return result;
}

#endif // DECINT_H
