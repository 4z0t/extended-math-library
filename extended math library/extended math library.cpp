

#include <iostream>
#include "DecInt.h"
#include "EMLIO.h"

void io_example()
{
	DecInt a{ 2,0,5325235 };
	a.print(true);
	std::cout << a;

}
int main()
{
	io_example();
}

