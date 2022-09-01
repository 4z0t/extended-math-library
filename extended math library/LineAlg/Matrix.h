#include<math.h>
#include <stdint.h>
#include <cassert>

#ifndef MATRIX_H
#define MATRIX_H


template <typename T, uint32_t Rows, uint32_t Colons = Rows >
class Matrix
{
	static_assert(Rows != 0 && Colons != 0);
public:

	typedef uint32_t SizeT;
private:
	struct _Indexer {
		uint32_t i, j;
	};

	T _data[Rows][Colons]{};

	friend class Matrix<T, Rows, Colons * 2>;
	friend class Matrix<T, Rows, Colons / 2>;


	Matrix<T, Rows, Colons * 2> extend()const;
	Matrix<T, Rows, Colons / 2> extract()const;
	void addrow(const int& targetrow, const int& addrow, const T& mult);
	void multraw(const int& targetrow, const T& mult);
	void swaprows(const SizeT& row1, const SizeT& row2);
public:

	const static SizeT rows = Rows;
	const static SizeT colons = Colons;
	const static SizeT size = Rows * Colons;


	Matrix();
	Matrix(const Matrix& other);
#ifdef _INITIALIZER_LIST_
	Matrix(std::initializer_list<T> data)
	{
		assert(data.size() == this->size, "std::initializer_list size doesn't match matrix size!");

		auto iter = data.begin();
		for (SizeT i = 0; i < this->rows; i++)
			for (SizeT j = 0; j < this->colons; j++)
			{
				this->_data[i][j] = *iter;
				iter++;
			}
	}
#endif
	~Matrix();

	static Matrix identity();


	Matrix& operator=(const Matrix& other);
	Matrix operator+(const Matrix& other)const;
	Matrix operator-(const Matrix& other)const;

	template <typename U, uint32_t S1, uint32_t S2, uint32_t S3 >
	friend Matrix<U, S1, S3> operator*(const Matrix<U, S1, S2>& first, const Matrix<U, S2, S3>& second);


	Matrix operator/(const Matrix& other)const;//A*B^-1
	Matrix operator%(const Matrix& other)const;//A^-1*B
	Matrix operator*(const T& value)const;
	Matrix operator/(const T& value)const;
	Matrix operator-()const;

	Matrix& operator+=(const Matrix& other);
	Matrix& operator-=(const Matrix& other);
	Matrix& operator*=(const Matrix& other);
	Matrix& operator*=(const T& value);
	Matrix& operator/=(const T& value);

	//boolean operations
	bool operator==(const Matrix& other)const;
	bool operator!=(const Matrix& other)const;
	bool zero()const;

	Matrix operator~()const;

	const T& get(const SizeT& i, const SizeT& j)const;
	void set(const SizeT& i, const SizeT& j, const T& value);




	void print();

	T& operator[](const _Indexer& indexer);
	const T& operator[](const _Indexer& indexer)const;


	//functions of matrices
	T trace()const;
	T det()const;
	T olddet()const;
	Matrix<T, Rows - 1, Colons - 1> minor(const SizeT& row, const SizeT& colon)const;
	Matrix transpose()const;
	Matrix adjugate()const;
	Matrix inverse()const;
	//template <class U> friend Matrix<U> pow(const Matrix<U>& other, const uint32_t& n);



};

template <typename U, uint32_t S1, uint32_t S2, uint32_t S3 >
Matrix<U, S1, S3> operator*(const Matrix<U, S1, S2>& first, const Matrix<U, S2, S3>& second);

template <typename T, uint32_t Rows, uint32_t Colons >
Matrix<T, Rows, Colons> operator*(const T& value, const Matrix<T, Rows, Colons>& other);

#ifdef _IOSTREAM_
template<typename T, uint32_t Rows, uint32_t Colons>
std::ostream& operator<<(std::ostream& os, const Matrix<T, Rows, Colons>& matrix);
#endif //_IOSTREAM_
#endif // !MATRIX_H
