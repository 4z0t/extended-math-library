#include <iostream>
#include <concepts>
//in your class must be implemented operators
// +
// *
// +=
// -=
// *=
// and ctor without parameters to malloc empty elements
// also you can implement your print method:

////template <class T>
////void Matrix<T>::print()
////{
////        for(int i = 0; i < this->rows;i++)
////        {
////           for(int j = 0; j < this->colons;j++)
////           {
////
////           }
////
////        }
////}

#ifndef MATRIX_H
#define MATRIX_H
#define INCORRECT_SIZE -2

template< typename T>
concept Matrix_operations = requires (T val)
{

	val + val;
	val - val;
	val / val;
	val* val;
	val != val;
	val == val;
};

template<typename T>
concept Appliable_to_matrix = Matrix_operations<T> &&
(
	std::convertible_to<float, T> ||
	std::convertible_to<int, T> ||
	std::convertible_to<double, T>
	);

template <Appliable_to_matrix T>
class Matrix
{
private:
	T** mat = nullptr;
	int rows = 0;
	int colons = 0;

	Matrix<T> extend()const;
	Matrix<T> extract()const;
	void addrow(const int& targetrow, const int& addrow, const T& mult);
	void multraw(const int& targetrow, const T& mult);
	void swaprows(const int& row1, const int& row2);
public:
	Matrix();
	~Matrix();

	Matrix<T>(const int& rows, const int& colons, T** const mtrx);
	Matrix<T>(const int& rows, const int& colons);
	Matrix<T>(const int& rows_colons);
	Matrix<T>(const Matrix<T>& other);



#ifdef _INITIALIZER_LIST_
	Matrix<T>(const int& rows, const int& colons, std::initializer_list<T> mtrx)
	{
		if (mtrx.size() != rows * colons)
			exit(INCORRECT_SIZE);
		this->mat = new T * [this->rows = rows];
		this->colons = colons;
		for (int i = 0; i < this->rows; i++)
			this->mat[i] = new T[this->colons]{};
		auto iter = mtrx.begin();
		for (int i = 0; i < this->rows; i++)
			for (int j = 0; j < this->colons; j++)
			{
				this->mat[i][j] = *iter;
				iter++;
			}
	}
#endif
	//operations with matrices
	Matrix<T>& operator=(const Matrix<T>& other);
	Matrix<T> operator+(const Matrix<T>& other)const;
	Matrix<T> operator-(const Matrix<T>& other)const;
	Matrix<T> operator*(const Matrix<T>& other)const;
	Matrix<T> operator/(const Matrix<T>& other)const;//A*B^-1
	Matrix<T> operator%(const Matrix<T>& other)const;//A^-1*B
	Matrix<T> operator*(const T& value)const;
	Matrix<T> operator/(const T& value)const;
	Matrix<T> operator-()const;

	Matrix<T>& operator+=(const Matrix<T>& other);
	Matrix<T>& operator-=(const Matrix<T>& other);
	Matrix<T>& operator*=(const Matrix<T>& other);
	Matrix<T>& operator*=(const T& value);
	Matrix<T>& operator/=(const T& value);

	//boolean operations
	bool operator==(const Matrix<T>& other)const;
	bool operator!=(const Matrix<T>& other)const;
	bool zero()const;

	Matrix<T> operator~()const;


	template <class U> friend Matrix<U> operator*(const U& value, const Matrix<U>& other);
	//other
	void print();
	T* operator[](const int& index);


	//functions of matrices
	T trace()const;
	T det()const;
	T olddet()const;
	Matrix<T> minor(const int& row, const int& colon)const;
	Matrix<T> transpose()const;
	Matrix<T> adjugate()const;
	Matrix<T> inverse()const;
	template <class U> friend Matrix<U> pow(const Matrix<U>& other, const uint32_t& n);


};

typedef Matrix<int>     Matrixi;
typedef Matrix<double>  Matrixd;


#endif // MATRIX_H
