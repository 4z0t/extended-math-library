

#include <iostream>
#include "DecInt.h"
#include "EMLIO.h"

void io_example()
{
	DecInt a{ 2,0,5325235 };
	a.print(true);
	std::cout << a;

}

void compare_test()
{
	DecInt a{ 2,0,5325235 };
	a.print(true);
	DecInt b({ 1,0 },false);
	b.print(true);

	std::cout << (a == b) << std::endl;
	std::cout << (a >= b) << std::endl;
	std::cout << (a <= b) << std::endl;
	std::cout << (a > b) << std::endl;
	std::cout << (a < b) << std::endl;

	
}
int main()
{
	//io_example();
	compare_test();
}

