
#include <iostream>
#include <fstream>
#include <initializer_list>
#include "Unlint.h"
#include "Unreal.h"
#include "Fraction.h"
#include "ioUnlimits.h"
#include "Unlconsts.h"
#include "Ubit.h"
#include "Ufloat.h"
#include "BitFrac.h"
#include "Matrix.cpp"
#include "Ringstash.h"
#include "Frac.h"
#include "Timer.h"
#include "Vector3.h"
#include <complex>
#include"Quaternion.h"

Unlint fact(uint32_t n)
{
	Unlint result = 1;
	for (uint32_t i = 2; i <= n; i++)
		result *= i;
	return result;
}
using namespace std;


//Unreal ln(const Unlint& value)
//{
//	if (value.zero())
//		exit(ZERO_ARGUMENT_ERROR_CODE);
//	if (value < 0)
//		exit(NEGATIVE_ARGUMENT_ERROR_CODE);
//	Fraction mult(value - 1, value + 1);
//	Fraction mult2 = pow(mult, 2);
//	uint64_t precision = Unreal::get_precision(); 
//	Fraction add;
//	Fraction result = 0;
//	uint32_t i = 1;
//	while (precision*9 >= -add.distance())
//	{
//		result += (add = mult / i);
//		i += 2;
//		mult *= mult2;
//	}
//	return ~(result*=2);
//}



Unreal abs(const Unreal& value)
{
	Unreal res = value;
	res.number.negative = false;
	return res;
}

Unreal ln(const Unreal& value)
{
	if (value.number.zero())
		exit(ZERO_ARGUMENT_ERROR_CODE);
	if (value < 0)
		exit(NEGATIVE_ARGUMENT_ERROR_CODE);
	uint32_t len = value.number.distance();
	Fraction mult(value.number - Unlint::ten(len - 1), value.number + Unlint::ten(len - 1));//wtf VS??? FIXIT ten() function
	//Fraction mult(value.number - ten(len - 1), value.number + ten(len - 1));//wtf VS??? FIXIT ten() function
	Fraction mult2 = pow(mult, 2);
	uint64_t precision = Unreal::get_precision();
	Fraction add;
	Fraction result = 0;
	uint32_t i = 1;
	while (precision * 9 >= -add.distance())
	{
		result += (add = mult / i);//modify
		i += 2;
		mult *= mult2;//modify
	}
	return ~(result *= 2) + U_LN10 * ((int)len - value.precision * 9 - 1);
}



void Ubit::print()const
{
	if (this->get_sign())
		cout << '-';
	cout << hex;
	for (uint32_t i = this->get_len() - 1;; i--)
	{
		cout << this->num[i] << '|';
		if (i == 0)break;
	}
	cout << dec << endl;;
}

void Ufloat::print()const
{
	if (this->number.get_sign())
		cout << '-';
	cout << hex;
	if (this->number.get_len() <= this->precision)
	{
		cout << '.';
		for (uint32_t i = 0; i < this->precision - this->number.get_len(); i++)
			cout << 0 << '|';
	}

	for (uint32_t i = this->number.get_len() - 1;; i--)
	{
		cout << this->number.num[i];
		if (i == this->precision)
			cout << '.';
		else
			cout << '|';
		if (i == 0)break;
	}
	cout << dec << endl;;
}


Ubit factbit(uint32_t n)
{
	Ubit result = 1;
	for (uint32_t i = 2; i <= n; i++)
		result = result * i;
	return result;
}

Ubit factbit(Ubit n)
{
	Ubit result = 1;
	for (Ubit i = 2; i <= n; i++)
		result = result * i;
	return result;
}

Ubit factbitdiv(const Ubit& val, uint32_t n)
{
	Ubit result = val;
	for (uint32_t i = 2; i <= n; i++)
		result = result / i;
	return result;
}

Unlint factdiv(const Unlint& val, uint32_t n)
{
	Unlint result = val;
	for (uint32_t i = 2; i <= n; i++)
		result /= i;
	return result;
}



Ubit fibbit(uint32_t n)
{
	Ubit a = 0;
	Ubit b = 1;
	Ubit c;
	for (uint32_t i = 0; i < n; i++)
	{
		c = a + b;
		a = b;
		b = c;
	}
	return a;
}

Unlint fib(uint32_t n)
{
	Unlint a = 0;
	Unlint b = 1;
	Unlint c;
	for (uint32_t i = 0; i < n; i++)
	{
		c = a + b;
		a = b;
		b = c;
	}
	return a;
}

Fraction Ufloat::convert() const
{
	Unlint a = this->number.cut(this->precision).convert();
	Fraction res = 0;
	Unlint mult = 1;
	Unlint two32 = 1;
	two32 += 0xffffffff;
	for (uint32_t i = this->precision - 1;; i--)
	{
		mult *= two32;
		if (i >= this->number.get_len())
			continue;
		res += Fraction(this->number.num[i], mult);
		if (i == 0)break;
	}
	return res + a;
}

template <Appliable_to_matrix T>
void Matrix<T>::print()
{
	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->colons; j++)
			std::cout << this->mat[i][j] << ' ';
		std::cout << std::endl;
	}
}

Ufloat cuberoot(const Ufloat& n)
{
	Ufloat prev = 0, res = 1;
	while (res != prev)
	{
		prev = res;
		res = res - (res * res * res - n) / 3 / res / res;
	}
	return res;
}

Unreal cuberoot(const Unreal& n)
{
	Unreal prev = 0, res = 1;
	while (res != prev)
	{
		prev = res;
		//res = (2 * res + n / (res * res)) / 3;
		res -= (res - n / (res * res)) / 3;
	}
	return res;
}




template<typename T>
concept convertible_to_complex_double = std::convertible_to<T, std::complex<double>>;


template<convertible_to_complex_double T>
std::complex<double> avgs(int& n, T val)
{
	return n++, val;
}
template<convertible_to_complex_double T, convertible_to_complex_double ... Ts>
std::complex<double> avgs(int& n, const T& val, const Ts...s)
{
	return val + avgs(++n, s...);
}
template<convertible_to_complex_double ... Ts>
std::complex<double> avg(const Ts...s)
{
	int n = 0;
	std::complex<double>  sum = avgs(n, s...);
	return sum / (double)n;
}


template<typename T, typename U>
concept bin_plus = requires(T a, U b) { a + b; };
template<typename T, typename U>
concept bin_minus = requires(T a, U b) { a - b; };

template<typename T, typename U>
concept plus_not_minus = bin_plus<T, U> && !bin_minus<T, U>;


template<typename T, typename U>
requires plus_not_minus<T,U>
T check_val(const T& a, const U& b)
{
	return a + b;
}



int main()
{
	//check_val(Unlint(5), 1);
	//check_val(6.6, 1);
	//std::cout<< check_val(std::string("f"), std::string("7"));














	Ufloat a = 1;
	Ufloat::set_precision(10);
	Fraction e = Fraction(U_E);
	Ufloat fle = Ufloat( e.get_numerator(),Ufloat::get_precision())


	//std::cout << avg(Quaternion(1, 1, 1, 1), 0.5, 4, 8, 6.7, std::complex<double>(2, 6), Quaternion(2, 2, 2, 2)) << std::endl;
	/*Matrix<float> a;
	Matrix<Unlint> b(3);
	b.print();
	Matrix<Ubit> t;
	Matrix<Unreal> u;*/
	/*Matrix<Ring<5>> r;
	Matrix<Frac> f;
	Ring<6> t;*/
	//Matrix<std::string> s; 
	//Matrix<Vector3<int>> v;

	//cout << (Frac(0) == 0);

	/*Matrix<Ring<3>> a(3, 3, { 2,1,0,
							0,0,2,
							1,0,2 });
	Matrix<Ring<3>> b(3, 3, { 0,2,1,
							1,2,1,
							0,2,0 });
	(a*b).print();
	(~a).print();
	Ring<3> c = 0;
	cout << -c << endl;*/
	/*Matrix<Fraction> a(2, 2,{2,1,
						-7,-3  });
	Matrix<Fraction> b(2, 2, { -1,3,
							0,2 });
	Matrix<Fraction> c(2, 2, { 1,1,
							1,1 });
	pow(a, 2008).print();*/

	/*Ubit a(10);
	a = factbit(a);
	Unlint b = factbit(a).convert();
	b.writebytestofile("10!!.unl");
	b.printinfile("10!!.txt");*/

	/*BitFrac s = 0;
	Ubit two = 2;
	Ubit fact1 = 1;

	for (uint32_t i = 1; i < 1000; i++)
	{
		fact1 *= i;
		s += BitFrac(fact1 * two, factbit(2 * i + 1));
		two *= 2;

	}
	s.convert().calculate().print();*/
	/*Unreal::set_precision(1);
	Unreal c = cuberoot(Unreal(7));
	c.print();
	(c * c * c).print();*/
	/*Unreal::set_precision(1);
	Unreal s = 0;
	Unreal one = 1;

	for (int i = 1; i < 1000000; i++)
	{

		s += one / cuberoot(Unreal(2 * i - 1));
		one *= -1;

	}
	s.print();*/

	/*Unreal::set_precision(100);
	Unreal a = Unreal(115) / 100;
	ln(a).print();*/
	/*Timer t;
	BitFrac e = Ubit(2);
	Ubit bitfac = 1;
	for (uint32_t i = 2; i < 1000; i++)
	{
		e += reciprocal(bitfac *= i);
	}

	cout << t.elapsed() << endl;
	e.convert().calculate(10).print();
	t.reset();
	Fraction ef = Unlint(2);
	Unlint factorial = 1;
	for (uint32_t i = 2; i < 1000; i++)
	{
		ef += reciprocal(factorial *= i);
	}
	cout << t.elapsed() << endl;
	ef.calculate(10).print();*/
	/*double** m = new double* [3];
	m[0] = new double[3]{ 1,3,2 };
	m[1] = new double[3]{ 4,2,5 };
	m[2] = new double[3]{ 7,3,1 };

	Matrixd A(3, 3, m);
	(A*A.inverse()).print();*/


	//ue.writebytestofile("e.txt");
	//ue.readbytesfromfile("e.txt");
	//e.convert().calculate(10).print();
	//Unlint a = pow(Unlint(2), 10000000);
	//a.printinfile("pow2.txt");
	//Timer t;
	//Ubit a = factbit(70000);
	//cout << t.elapsed() << endl;
	////a.convert().printinfile("dfklfdf");
	//t.reset();
	//Unlint b = fact(70000);
	//cout << t.elapsed() << endl;


	//U_PI.print();


	//(a <<= 11).convert().print();
	//a.movethiscells(10).convert().print();

	//U_E.print();

	/*Int a = factbit(1000);

	Unlint b = fact(1000);

	Timer t;
	a = factbitdiv(a, 1000);
	cout << t.elapsed() << endl;
	t.reset();
	b = factdiv(b, 1000);
	cout << t.elapsed() << endl;
	b.print();
	a.convert().print();*/

	/*Ubit a = 8382;
	a.movethiscells(1);
	a += 3878233;
	a.print();
	Ubit b = 2654647;
	b.movethiscells(1);
	b += 2252362;
	b.print();

	(a | b).print();
	(a & b).print();*/

	/*Ubit a = mask;
	a.movethiscells(2);
	a.print();
	Ubit b = mask;
	b.movethiscells(1);
	a /= b;
	a.print();*/


	/*Ubit a = 436246;
	a.movethiscells(1) += 8743847;
	a.movethiscells(1) += 547447;
	a.print();
	Ubit b = 823289;
	b.movethiscells(1) += 24234;
	Unlint au = a.convert();
	Unlint bu = b.convert();
	au.print();
	bu.print();
	((a + a / b)/2).convert().print();
	((au + au / bu) / 2).print();*/



	/*Ufloat b = 3565642;
	Unreal au = 547434, bu = 3565642;
	(au / bu).print();

	(a / b).convert().calculate(4).print();*/
	/*int a = 3;
	cout << hex << (mask << (32 - a)) << endl;
	cout << hex << (mask << (a)) << endl;*/
	/*Ufloat::set_precision(10);
	Unreal::set_precision(10);
	Timer t;
	Ufloat a = 54;
	a = sqrt(a);
	cout << t.elapsed() << endl;
	t.reset();
	Unreal c = 54;
	c = sqrt(c);
	cout << t.elapsed() << endl;
	Unreal b = a.convert().calculate(10);
	(b * b).print();*/

	/*Ubit a = 213;
	a.movethiscells(2);
	a += 43324;
	Unlint au = a.convert();
	Ubit b = 726362;
	b.movethiscells(1);
	Unlint bu = b.convert();
	a.convert().print();
	b.convert().print();
	au.print();
	bu.print();
	(a - b).convert().print();
	(au - bu).print();*/

	//cout << (b == a.convert()) << endl;
	//b.print();
	//a.print();
	//b.print();
	//a.convert().print();

	/*sum n = smart_sum(0x80000001, 0);
	cout << n.rest << ' ' << hex << n.num << endl;*/
	/*uint64_t d = (uint64_t)mask * mask_last_bit;
	cout <<hex<< d << endl;*/
	/*Ubit a = mask;
	Ubit b = last_bit;
	Ubit c = -a + (b);
	c.print();*/
	//cout << sizeof(sum) << endl;
	/*Ubit  a = mask_last_bit;
	Unlint ai = mask_last_bit;
	Ubit b = last_bit;
	Unlint bi = last_bit;
	Unlint ci = ai * bi * 5765656565u * 5765656565u * 5765656565u * 5765656565u;
	Ubit c = a * b * 5765656565u * 5765656565u * 5765656565u * 5765656565u;
	c.convert().print();
	ci.print();*/
	/*double a = -0.0000005;
	cout << a << endl;
	const Unreal ua = a;
	ua.print();
	cout << (double)ua << endl;*/
	//cout << U_LN10 << endl;
	/*Unreal a = U_PI;
	a /= 4;
	a *= 2;
	cout << a << endl;*/
	//Unreal  b = pow(Unlint(101), 28);
	//
	////b.print();
	//double a = double(b);
	////printf("%1.10f", a);
	//cout <<a << endl;
	//a = float(U_E);

	//cout << a << endl;

	/*float  a;
	uint32_t rep = 0x41e00000;
	float b =* (float*)&rep;
	std::memcpy(&a, &rep, sizeof a);
	cout << a << endl;
	cout << b << endl;*/
	/*uint8_t a = 0b10000000;
	cout << int(a) << endl;*/

	/*Unreal::set_precision(10);
	Unlint a = 412;
	Unreal b = ln(a);
	b.print();*/
	/*Unreal a("sqrt3.txt");
	Unreal b("sqrt2.txt");
	cout << a <<endl << b << endl;*/




	///////////////////////// 
////PI CALC
	//Unreal::set_precision(10);
	//Fraction pi = 0;
	//int one = 1;
	//Unlint num;
	//Unlint den;
	//const Unlint a = 545140134u;
	////const Unlint b = pow(Unlint(640320), 3);
	////b.writebytestofile("b");
	//const Unlint b("b");
	//Unlint t = 1;
	//Unlint m = 0;
	//Unreal c("c");
	////c.readbytesfromfile("c");
	////Unreal c = b;
	//c = sqrt(c);
	//c.writebytestofile("c");
	//for (uint32_t i = 0; i < 10; i++)
	//{
	//	if (i % 2)
	//		num = -fact(6 * i) * (m + 13591409);
	//	else
	//		num = fact(6 * i) * (m + 13591409);
	//	m += a;
	//	//den = fact(3 * i) * pow(fact(i), 3) * pow(b, 3 * i);
	//	den = fact(3 * i) * pow(fact(i), 3) * t;
	//	t *= b;
	//	pi += Fraction(num, den);
	//}
	//pi *= 12;
	//Unreal p = (~reciprocal(pi)) * c;
	//p.print();
	//p.writebytestofile("pi.txt");

	//////////////////////////////////////
//Fraction a = 1;
//for (uint32_t i = 0; i < 100; i++)
//{
//	a = a / (reciprocal(pow(2, i)) + 1);
//	//(~reciprocal(a)).print();
//}
//(~reciprocal(a)).print();

/*Unlint a = 3;
a = pow(a, 3);
cout << a << endl;
*/
//Unreal b = 3;
//b = sqrt(b);
//b.writebytestofile("sqrt3.txt");
/* Unlint a = 2;
a = pow(a, 100);
a.print();*/
/*Unlint a = 0;
Unlint b = 1;
Unlint c ;
for (uint32_t i = 0; i < 100; i++)
{
	c = a + b;
	a = b;
	b = c;
}
a.print();*/
/*Unlint a = 1219219723;
Unlint b = 17;
Unlint c = a / b;
c.print();*/


//Fraction e = Unlint(0);
//for (uint32_t i = 0; i < 100; i++)
//{
//	e += reciprocal(fact(i));
//}
//Unreal ue = e.calculate(10);
////ue.writebytestofile("e.txt");
////ue.readbytesfromfile("e.txt");
//ue.print();
//2.718281828459045235360287471352662497757247093699959574966967627724076630353547594571382178
//2.718281828459045235360287471352662497757247093699959574966967627724076630353547594571382178
//2.718281828459045235360287471352662497757247093699959574966967627724076630353547594571382178




// char* num = cstring(a);
//std::ofstream file;
//file.open("fib.txt");
//file <<num << std::endl;
//file.close();

//

//
//delete[] num;
  // delete[]byte;

	return 0;
}
