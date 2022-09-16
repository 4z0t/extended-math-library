

#include <iostream>
#include <fstream>
#include <utility>
#include "DecInt.h"
#include "BinInt.h"
#include "EMLIO.h"
#include "Functions.h"
#include "Timer.h"


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
	DecInt b({ 1,0 }, false);
	b.print(true);

	std::cout << (a == b) << std::endl;
	std::cout << (a >= b) << std::endl;
	std::cout << (a <= b) << std::endl;
	std::cout << (a > b) << std::endl;
	std::cout << (a < b) << std::endl;
}

#if _DEBUG
void debug_test()
{
	DecInt a{ 0,0,5325235 };
	a.debug_log();
}


void sum_sub_test()
{
	DecInt a = { 999999999,999132914 ,546547 };
	a.debug_log();
	DecInt b = { 1213214 ,0 };
	b.debug_log();
	DecInt c = b + a;
	c.debug_log();
	DecInt d = b - a;
	d.print(true);
	DecInt e = a - b;
	e.print(true);

	/*(a + b).print();
	(a - b).print();
	(b - a).print();*/

}
//void cut_move_test()
//{
//	DecInt a{ 2,0,5325235 };
//	DecInt b= a.movecells(5);
//	DecInt c = a.cut(1);
//	c.print(true);
//	b.print(true);
//}

void copy_test()
{
	DecInt a = { 999999999,999132914 ,546547 };
	a.debug_log();
	DecInt b = { 1213214 ,0 };
	b.debug_log();
	b = a;
	b.debug_log();

}

void mult_test()
{
	DecInt a = { 999999999,999132914 ,546547 };
	a.debug_log();
	DecInt b = { 1213214 ,0 };
	b.debug_log();
	DecInt c = -b * -b;
	c.debug_log();
	std::cout << c;

}


void move10_test()
{

	DecInt a = { 0,0, 999999999,999132914 ,546547 };
	a.debug_log();
	DecInt b = { 1213214 ,0 };
	b.debug_log();
	DecInt c = a.move10(19);
	a.movethis10(19);
	assert(a == c);
	c.debug_log();
	a.debug_log();
	std::cout << c;
	std::cout << a;
}


void div_test()
{
	DecInt a = { 0,0, 999999999,999132914 ,546547 };
	a.debug_log();
	DecInt b = { 1213214 ,0 };
	b.debug_log();

	DecInt c = a * b;
	DecInt d = c / b;
	d.debug_log();
	assert(d == a);
	DecInt e = c / a;
	e.debug_log();
	assert(e == b);

	DecInt z = 0;
	e = a / (-a);
	e.debug_log();




}


void modulo_test()
{
	DecInt a = { 0,0, 999999999,999132914 ,546547 };
	a.debug_log();
	DecInt b = { 1213214 ,0 };
	b.debug_log();

	DecInt n = a / b;

	DecInt c = a % b;
	c.debug_log();

	DecInt aa = n * b + c;
	aa.debug_log();
	assert(aa == a);

	DecInt d = b % a;
	d.debug_log();

}

void test()
{

	DecInt a = 5;
	DecInt b = a;
	DecInt c = a + b;
	c.debug_log();

}

void mult_test2()
{
	DecInt a = { 1 ,999'999'999 };
	a.debug_log();
	DecInt b = { 1 ,999'999'999 };
	b.debug_log();
	DecInt c = a * b;
	c.debug_log();
}
#endif
void test_factorial()
{
	std::ofstream file;
	file.open("fact100000.txt");
	DecInt f = dec_factorial(100000);
	file << f;
}
void btest_factorial()
{
	std::ofstream file;
	file.open("fact100000.txt");
	BinInt f = bin_factorial(100000);
	file << f;
}

void test_DecInt()
{
	//test();
	//io_example();
	//compare_test();
	//debug_test();
	//cut_move_test();
	//sum_sub_test();
	//copy_test();
	//mult_test();
	//move10_test();
	//div_test();
	//modulo_test();
	//test_factorial();
	//mult_test2();
}
#if _DEBUG
void btest_sum()
{
	BinInt a = { 1,1 };
	a.debug_log();
	BinInt b = { 2,0xffaabbcc };
	b.debug_log();
	BinInt c = a + b;
	c.debug_log();
	BinInt d = a - b;
	d.debug_log();
	BinInt e = b - a;
	e.debug_log();


}
#endif


void compare_speed()
{
	Timer t;

	dec_fib(1000000);
	double d = t.elapsed();
	std::cout << d << std::endl;
	t.reset();
	bin_fib(1000000);
	d = t.elapsed();
	std::cout << d << std::endl;
}

int main()
{

	compare_speed();
}

