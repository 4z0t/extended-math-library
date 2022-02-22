

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

void debug_test()
{
	DecInt a{ 0,0,5325235 };
	a.debug_log();
}

//void cut_move_test()
//{
//	DecInt a{ 2,0,5325235 };
//	DecInt b= a.movecells(5);
//	DecInt c = a.cut(1);
//	c.print(true);
//	b.print(true);
//}

int main()
{
	//io_example();
	//compare_test();
	//debug_test();
	//cut_move_test();
}

