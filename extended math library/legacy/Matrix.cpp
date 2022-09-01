#include "..\LineAlg\Matrix.h"

// //created by 4z0t


// #include "Matrix.h"




// template <Appliable_to_matrix T>
// Matrix<T>::Matrix()
// {
// 	this->mat = nullptr;
// 	this->colons = 0;
// 	this->rows = 0;
// }

// template <Appliable_to_matrix T>
// Matrix<T>::~Matrix()
// {
// 	if (this->mat != nullptr)
// 	{
// 		for (int i = 0; i < this->rows; i++)
// 			delete[] this->mat[i];
// 		delete[] this->mat;
// 	}
// }

// template <Appliable_to_matrix T>
// Matrix<T>::Matrix(const int& rows, const int& colons, T** const mtrx)
// {
// 	this->mat = new T * [this->rows = rows];
// 	this->colons = colons;
// 	for (int i = 0; i < this->rows; i++)
// 		this->mat[i] = new T[this->colons]{};
// 	if (mtrx != nullptr)
// 	{
// 		for (int i = 0; i < this->rows; i++)
// 			for (int j = 0; j < this->colons; j++)
// 				this->mat[i][j] = mtrx[i][j];
// 	}
// }

// template <Appliable_to_matrix T>
// Matrix<T>::Matrix(const int& rows, const int& colons)
// {
// 	this->mat = new T * [this->rows = rows];
// 	this->colons = colons;
// 	for (int i = 0; i < this->rows; i++)
// 		this->mat[i] = new T[this->colons]{};
// }

// template <Appliable_to_matrix T>
// Matrix<T>::Matrix(const int& rows_colons)
// {
// 	this->mat = new T * [this->rows = rows_colons];
// 	this->colons = rows_colons;
// 	for (int i = 0; i < this->rows; i++)
// 	{
// 		this->mat[i] = new T[this->colons]{};
// 		mat[i][i] = 1;
// 	}
// }


// template <Appliable_to_matrix T>
// Matrix<T>::Matrix(const Matrix<T>& other)
// {
// 	this->mat = new T * [this->rows = other.rows];
// 	this->colons = other.colons;
// 	for (int i = 0; i < this->rows; i++)
// 	{
// 		this->mat[i] = new T[this->colons]{};
// 		for (int j = 0; j < this->colons; j++)
// 			this->mat[i][j] = other.mat[i][j];
// 	}
// }

// template <Appliable_to_matrix T>
// Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other)
// {
// 	if (this->mat != nullptr)
// 	{
// 		for (int i = 0; i < this->rows; i++)
// 			delete[] this->mat[i];
// 		delete[] this->mat;
// 	}
// 	this->mat = new T * [this->rows = other.rows];
// 	this->colons = other.colons;
// 	for (int i = 0; i < this->rows; i++)
// 	{
// 		this->mat[i] = new T[this->colons]{};
// 		for (int j = 0; j < this->colons; j++)
// 			this->mat[i][j] = other.mat[i][j];
// 	}
// 	return *this;
// }

// template <Appliable_to_matrix T>
// Matrix<T> Matrix<T>::operator+(const Matrix<T>& other)const
// {
// 	if (this->colons == other.colons && this->rows == other.rows)
// 	{
// 		Matrix<T> new_matrix = *this;
// 		for (int i = 0; i < new_matrix.rows; i++)
// 			for (int j = 0; j < new_matrix.colons; j++)
// 				new_matrix.mat[i][j] += other.mat[i][j];
// 		return new_matrix;
// 	}
// 	else
// 	{
// 		throw"In Matrix: error: unable to sum matrices, please, read about rules of summing matrices";

// 	}
// }

// template <Appliable_to_matrix T>
// Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& other)
// {
// 	if (this->colons == other.colons && this->rows == other.rows)
// 	{
// 		for (int i = 0; i < this->rows; i++)
// 			for (int j = 0; j < this->colons; j++)
// 				this->mat[i][j] += other.mat[i][j];
// 		return *this;
// 	}
// 	else
// 	{
// 		throw "In Matrix: error: unable to sum matrices, please, read about rules of summing matrices";
// 	}
// }

// template <Appliable_to_matrix T>
// Matrix<T> Matrix<T>::operator-(const Matrix<T>& other)const
// {
// 	if (this->colons == other.colons && this->rows == other.rows)
// 	{
// 		Matrix<T> new_matrix = *this;
// 		for (int i = 0; i < new_matrix.rows; i++)
// 			for (int j = 0; j < new_matrix.colons; j++)
// 				new_matrix.mat[i][j] -= other.mat[i][j];
// 		return new_matrix;
// 	}
// 	else
// 	{
// 		throw "In Matrix: error: unable to subtract matrices, please, read about rules of subtracting matrices";

// 	}
// }

// template <Appliable_to_matrix T>
// Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& other)
// {
// 	if (this->colons == other.colons && this->rows == other.rows)
// 	{
// 		for (int i = 0; i < this->rows; i++)
// 			for (int j = 0; j < this->colons; j++)
// 				this->mat[i][j] -= other.mat[i][j];
// 		return *this;
// 	}
// 	else
// 	{
// 		throw  "In Matrix: error: unable to subtract matrices, please, read about rules of subtracting matrices";
// 	}
// }

// template <Appliable_to_matrix T>
// Matrix<T> Matrix<T>::operator*(const Matrix<T>& other)const
// {
// 	if (this->colons == other.rows)
// 	{
// 		Matrix<T> new_matrix(this->rows, other.colons, nullptr);
// 		for (int i = 0; i < new_matrix.rows; i++)
// 			for (int j = 0; j < new_matrix.colons; j++)
// 				for (int k = 0; k < this->colons; k++)
// 					new_matrix.mat[i][j] += this->mat[i][k] * other.mat[k][j];
// 		return new_matrix;
// 	}
// 	else
// 	{
// 		throw "In Matrix: error: unable to multiply matrices, please, read about rules of multiplying matrices";
// 	}
// }

// template <Appliable_to_matrix T>
// Matrix<T> Matrix<T>::operator/(const Matrix<T>& other)const
// {
// 	return *this * other.inverse();
// }

// template <Appliable_to_matrix T>
// Matrix<T> Matrix<T>::operator%(const Matrix<T>& other)const
// {
// 	return this.inverse() * other;
// }

// template <Appliable_to_matrix T>
// Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& other)
// {
// 	if (this->colons == other.rows)
// 	{
// 		Matrix<T> new_matrix(this->rows, other.colons, nullptr);
// 		for (int i = 0; i < new_matrix.rows; i++)
// 			for (int j = 0; j < new_matrix.colons; j++)
// 				for (int k = 0; k < this->colons; k++)
// 					new_matrix.mat[i][j] += this->mat[i][k] * other.mat[k][j];
// 		return*this = new_matrix;
// 	}
// 	else
// 	{
// 		throw "In Matrix: error: unable to multiply matrices, please, read about rules of multiplying matrices";
// 	}
// }

// template <Appliable_to_matrix T>
// Matrix<T> Matrix<T>::operator*(const T& value)const
// {
// 	Matrix<T> new_matrix = *this;
// 	for (int i = 0; i < new_matrix.rows; i++)
// 		for (int j = 0; j < new_matrix.colons; j++)
// 			new_matrix.mat[i][j] *= value;
// 	return new_matrix;
// }

// template <Appliable_to_matrix T>
// Matrix<T>& Matrix<T>::operator*=(const T& value)
// {
// 	for (int i = 0; i < this->rows; i++)
// 		for (int j = 0; j < this->colons; j++)
// 			this->mat[i][j] *= value;
// 	return *this;
// }

// template <Appliable_to_matrix T>
// Matrix<T> Matrix<T>::operator/(const T& value)const
// {
// 	Matrix<T> new_matrix = *this;
// 	for (int i = 0; i < new_matrix.rows; i++)
// 		for (int j = 0; j < new_matrix.colons; j++)
// 			new_matrix.mat[i][j] /= value;
// 	return new_matrix;
// }


// template <Appliable_to_matrix T>
// Matrix<T>& Matrix<T>::operator/=(const T& value)
// {
// 	for (int i = 0; i < this->rows; i++)
// 		for (int j = 0; j < this->colons; j++)
// 			this->mat[i][j] /= value;
// 	return *this;
// }

// template <Appliable_to_matrix T>
// Matrix<T> operator*(const T& value, const Matrix<T>& other)
// {
// 	Matrix<T> new_matrix = other;
// 	for (int i = 0; i < new_matrix.rows; i++)
// 		for (int j = 0; j < new_matrix.colons; j++)
// 			new_matrix.mat[i][j] *= value;
// 	return new_matrix;
// }

// template <Appliable_to_matrix T>
// T* Matrix<T>::operator[](const int& index)
// {
// 	//FIXIT
// 	//add Appliable_to_matrix "Row"
// 	//elements of matrix does not have index 0
// 	//indexes begin with 1
// 	return mat[index];
// }

// template <Appliable_to_matrix T>
// Matrix<T> Matrix<T>::operator-()const
// {
// 	Matrix<T> new_matrix = *this;
// 	for (int i = 0; i < new_matrix.rows; i++)
// 		for (int j = 0; j < new_matrix.colons; j++)
// 			new_matrix.mat[i][j] = -new_matrix.mat[i][j];
// 	return new_matrix;
// }


// template <Appliable_to_matrix T>
// Matrix<T> Matrix<T>::operator~()const
// {

// 	Matrix<T> extention = this->extend();
// 	for (int i = 0; i < this->colons; i++)
// 	{
// 		if (extention.mat[i][i] == 0)
// 		{
// 			bool broken = false;
// 			for (int j = i + 1; j < this->rows; j++)
// 				if (extention.mat[j][i] != 0)
// 				{
// 					extention.swaprows(i, j);
// 					broken = true;
// 					break;
// 				}
// 			if (!broken)
// 				throw "determinant is 0";
// 		}

// 		for (int j = i + 1; j < this->rows; j++)
// 			if (extention.mat[j][i] != 0)
// 				extention.addrow(j, i, -extention.mat[j][i] / extention.mat[i][i]);
// 	}



// 	for (int i = this->colons - 1; i != 0; i--)
// 		for (int j = i - 1; ; j--)
// 			if (extention.mat[i][i] != 0)
// 			{
// 				if (extention.mat[j][i] != 0)
// 					extention.addrow(j, i, -extention.mat[j][i] / extention.mat[i][i]);
// 				/*std::cout << "////////" << std::endl;
// 				extention.print();*/
// 				if (j == 0)break;
// 			}
// 			else
// 			{
// 				throw "determinant is 0";
// 			}
// 	for (int i = 0; i < this->rows; i++)
// 		if (extention.mat[i][i] == 0)
// 			throw "determinant is 0";
// 		else
// 			extention.multraw(i, T(1) / extention.mat[i][i]);
// 	return extention.extract();
// }

// template <Appliable_to_matrix T>
// void Matrix<T>::swaprows(const int& row1, const int& row2)
// {
// 	T* temp = this->mat[row1];
// 	this->mat[row1] = this->mat[row2];
// 	this->mat[row2] = temp;

// }

// template <Appliable_to_matrix T>
// Matrix<T> Matrix<T>::extract()const
// {
// 	Matrix<T> newmat(this->rows, this->colons / 2);
// 	for (int i = 0; i < this->rows; i++)
// 	{
// 		for (int j = newmat.colons; j < this->colons; j++)
// 			newmat.mat[i][j - newmat.colons] = this->mat[i][j];
// 	}
// 	return newmat;
// }


// template <Appliable_to_matrix T>
// void Matrix<T>::addrow(const int& targetrow, const int& addrow, const T& mult)
// {
// 	for (int j = 0; j < this->colons; j++)
// 		this->mat[targetrow][j] += this->mat[addrow][j] * mult;
// }

// template <Appliable_to_matrix T>
// void Matrix<T>::multraw(const int& targetrow, const T& mult)
// {
// 	for (int j = 0; j < this->colons; j++)
// 		this->mat[targetrow][j] *= mult;
// }

// template <Appliable_to_matrix T>
// Matrix<T> Matrix<T>::extend()const
// {
// 	Matrix<T> newmat(this->rows, this->colons * 2);
// 	for (int i = 0; i < this->rows; i++)
// 	{
// 		for (int j = 0; j < this->colons; j++)
// 			newmat.mat[i][j] = this->mat[i][j];

// 		for (int j = this->colons; j < newmat.colons; j++)
// 			if (i == j - this->colons)
// 				newmat.mat[i][j] = 1;
// 			else
// 				newmat.mat[i][j] = 0;
// 	}
// 	return newmat;
// }

// template <Appliable_to_matrix T>
// T Matrix<T>::olddet()const
// {
// 	if (this->rows == this->colons)
// 	{
// 		if (this->rows == 1)
// 			return this->mat[0][0];

// 		if (this->colons == this->rows)
// 		{
// 			T result = 0;
// 			int one = -1;
// 			for (int i = 0; i < this->rows; i++)
// 				result += this->mat[i][0] * this->minor(i, 0).olddet() * (one *= -1);
// 			return result;
// 		}
// 	}
// 	else
// 	{
// 		throw "In Matrix: error: unable to find determinant of Matrix, matrix is not square";

// 	}
// }

// template <Appliable_to_matrix T>
// T Matrix<T>::det()const
// {
// 	if (this->rows == this->colons)
// 	{
// 		Matrix<T> extention = this->extend();
// 		for (int i = 0; i < this->colons; i++)
// 		{
// 			if (extention.mat[i][i] == 0)
// 			{
// 				bool broken = false;
// 				for (int j = i + 1; j < this->rows; j++)
// 					if (extention.mat[j][i] != 0)
// 					{
// 						extention.swaprows(i, j);
// 						broken = true;
// 						break;
// 					}
// 				if (!broken)
// 					return 0;
// 			}
// 			for (int j = i + 1; j < this->rows; j++)
// 				if (extention.mat[j][i] != 0)
// 					extention.addrow(j, i, -extention.mat[j][i] / extention.mat[i][i]);
// 		}

// 		T res = 1;
// 		for (int i = 0; i < this->colons; i++)
// 			res *= extention.mat[i][i];
// 		return res;
// 	}
// 	else
// 	{
// 		throw  "In Matrix: error: unable to find determinant of Matrix, matrix is not square";
// 	}
// }

// template <Appliable_to_matrix T>
// T Matrix<T>::trace()const
// {
// 	if (this->rows == this->colons)
// 	{
// 		T result = 0;
// 		for (int i = 0; i < this->rows; i++)
// 			result += this->mat[i][i];
// 		return result;
// 	}
// 	else
// 	{
// 		throw "In Matrix: error: unable to find trace of Matrix, matrix is not square";
// 	}
// }

// template <Appliable_to_matrix T>
// Matrix<T> Matrix<T>::minor(const int& row, const int& colon)const
// {
// 	Matrix<T> new_matrix(this->rows - 1, this->colons - 1);
// 	for (int i = 0, ni = 0; ni < new_matrix.rows; i++, ni++)
// 		for (int j = 0, nj = 0; nj < new_matrix.colons; j++, nj++)
// 		{
// 			if (row == i)
// 				i++;
// 			if (colon == j)
// 				j++;
// 			new_matrix.mat[ni][nj] = this->mat[i][j];
// 		}
// 	return new_matrix;
// }

// template <Appliable_to_matrix T>
// Matrix<T> Matrix<T>::transpose()const
// {
// 	Matrix<T> new_matrix(this->colons, this->rows);
// 	for (int i = 0; i < new_matrix.rows; i++)
// 		for (int j = 0; j < new_matrix.colons; j++)
// 			new_matrix.mat[i][j] = this->mat[j][i];
// 	return new_matrix;
// }

// template <Appliable_to_matrix T>
// Matrix<T> Matrix<T>::adjugate()const
// {
// 	Matrix<T> new_matrix(this->rows, this->colons);
// 	for (int i = 0; i < new_matrix.rows; i++)
// 		for (int j = 0; j < new_matrix.colons; j++)
// 			new_matrix.mat[i][j] = this->minor(i, j).det() * (1 - ((i + j) % 2) * 2);
// 	return new_matrix;
// }

// template <Appliable_to_matrix T>
// Matrix<T> Matrix<T>::inverse()const
// {
// 	if (this->det() != 0)
// 		return this->adjugate().transpose() / this->det();
// 	else
// 	{
// 		throw "In Matrix: error: unable to find inverse Matrix, determinant equals to 0";

// 	}
// }

// template <Appliable_to_matrix T>
// bool Matrix<T>::operator==(const Matrix<T>& other)const
// {
// 	if (this->rows == other.raws && this->colons == other.colons)
// 	{
// 		for (int i = 0; i < this->rows; i++)
// 			for (int j = 0; j < this->colons; j++)
// 				if (this->mat[i][j] != other.mat[i][j])
// 					return false;
// 		return true;
// 	}
// 	else
// 		return false;
// }

// template <Appliable_to_matrix T>
// bool Matrix<T>::operator!=(const Matrix<T>& other)const
// {
// 	return !(*this == other);
// }

// //TODO: change
// template<Appliable_to_matrix T>
// Matrix<T> one(const int& size)
// {
// 	return Matrix<T>(size);
// }


// template<Appliable_to_matrix T>
// bool Matrix<T>::zero() const
// {
// 	for (int i = 0; i < this->rows; i++)
// 		for (int j = 0; j < this->colons; j++)
// 			if (this->mat[i][j] != 0)
// 				return false;
// 	return true;
// }

// template<Appliable_to_matrix T>
// Matrix<T> pow(const Matrix<T>& other, const uint32_t& n)
// {
// 	Matrix<T> result(other.rows);
// 	Matrix<T> buffer = other;
// 	for (uint8_t i = 0; i < sizeof(n) * 8 && (1 << i) <= n; i++)
// 	{
// 		//std::cout << i << std::endl;
// 		if (n & (1 << i))
// 			result *= buffer;
// 		if ((1 << i) < n)
// 			buffer *= buffer;
// 	}
// 	return result;
// }

