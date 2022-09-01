#include "Matrix.h"




template <typename T, uint32_t Rows, uint32_t Colons >
Matrix<T, Rows, Colons>::Matrix()
{

}

template <typename T, uint32_t Rows, uint32_t Colons >
Matrix<T, Rows, Colons>::~Matrix()
{

}

template<typename T, uint32_t Rows, uint32_t Colons>
Matrix<T, Rows, Colons> Matrix<T, Rows, Colons>::identity()
{
	static_assert(Rows == Colons);
	Matrix<T, Rows, Colons> result;
	for (SizeT i = 0; i < Rows; i++)
	{
		result._data[i][i] = 1;
	}
	return result;
}

template <typename T, uint32_t Rows, uint32_t Colons >
Matrix<T, Rows, Colons>::Matrix(const Matrix<T, Rows, Colons>& other)
{

	for (SizeT i = 0; i < this->rows; i++)
	{
		for (SizeT j = 0; j < this->colons; j++)
			this->_data[i][j] = other._data[i][j];
	}
}

template <typename T, uint32_t Rows, uint32_t Colons >
Matrix<T, Rows, Colons>& Matrix<T, Rows, Colons>::operator=(const Matrix<T, Rows, Colons>& other)
{
	for (SizeT i = 0; i < this->rows; i++)
	{
		for (SizeT j = 0; j < this->colons; j++)
			this->_data[i][j] = other._data[i][j];
	}
	return *this;
}

template <typename T, uint32_t Rows, uint32_t Colons >
Matrix<T, Rows, Colons> Matrix<T, Rows, Colons>::operator+(const Matrix<T, Rows, Colons>& other)const
{

	Matrix<T, Rows, Colons> new_matrix = *this;
	for (SizeT i = 0; i < new_matrix.rows; i++)
		for (SizeT j = 0; j < new_matrix.colons; j++)
			new_matrix._data[i][j] += other._data[i][j];
	return new_matrix;
}

template <typename T, uint32_t Rows, uint32_t Colons >
Matrix<T, Rows, Colons>& Matrix<T, Rows, Colons>::operator+=(const Matrix<T, Rows, Colons>& other)
{

	for (SizeT i = 0; i < this->rows; i++)
		for (SizeT j = 0; j < this->colons; j++)
			this->_data[i][j] += other._data[i][j];
	return *this;

}

template <typename T, uint32_t Rows, uint32_t Colons >
Matrix<T, Rows, Colons> Matrix<T, Rows, Colons>::operator-(const Matrix<T, Rows, Colons>& other)const
{

	Matrix<T, Rows, Colons> new_matrix = *this;
	for (SizeT i = 0; i < new_matrix.rows; i++)
		for (SizeT j = 0; j < new_matrix.colons; j++)
			new_matrix._data[i][j] -= other._data[i][j];
	return new_matrix;


}


template <typename T, uint32_t Rows, uint32_t Colons >
Matrix<T, Rows, Colons>& Matrix<T, Rows, Colons>::operator-=(const Matrix<T, Rows, Colons>& other)
{

	for (SizeT i = 0; i < this->rows; i++)
		for (SizeT j = 0; j < this->colons; j++)
			this->_data[i][j] -= other._data[i][j];
	return *this;

}

template<typename U, uint32_t S1, uint32_t S2, uint32_t S3>
inline Matrix<U, S1, S3> operator*(const Matrix<U, S1, S2>& first, const Matrix<U, S2, S3>& second)
{
	Matrix<U, S1, S3> new_matrix;
	for (uint32_t i = 0; i < S1; i++)
		for (uint32_t j = 0; j < S3; j++)
			for (uint32_t k = 0; k < S2; k++)
				new_matrix._data[i][j] += first._data[i][k] * second._data[k][j];
	return new_matrix;
}




template <typename T, uint32_t Rows, uint32_t Colons >
Matrix<T, Rows, Colons> Matrix<T, Rows, Colons>::operator/(const Matrix<T, Rows, Colons>& other)const
{
	return *this * other.inverse();
}

template <typename T, uint32_t Rows, uint32_t Colons >
Matrix<T, Rows, Colons> Matrix<T, Rows, Colons>::operator%(const Matrix<T, Rows, Colons>& other)const
{
	return this.inverse() * other;
}

template <typename T, uint32_t Rows, uint32_t Colons >
Matrix<T, Rows, Colons>& Matrix<T, Rows, Colons>::operator*=(const Matrix<T, Rows, Colons>& other)
{

	Matrix<T, Rows, Colons> new_matrix;
	for (SizeT i = 0; i < new_matrix.rows; i++)
		for (SizeT j = 0; j < new_matrix.colons; j++)
			for (SizeT k = 0; k < this->colons; k++)
				new_matrix._data[i][j] += this->_data[i][k] * other._data[k][j];
	return*this = new_matrix;

}

template <typename T, uint32_t Rows, uint32_t Colons >
Matrix<T, Rows, Colons> Matrix<T, Rows, Colons>::operator*(const T& value)const
{
	Matrix<T, Rows, Colons> new_matrix = *this;
	for (SizeT i = 0; i < new_matrix.rows; i++)
		for (SizeT j = 0; j < new_matrix.colons; j++)
			new_matrix._data[i][j] *= value;
	return new_matrix;
}

template <typename T, uint32_t Rows, uint32_t Colons >
Matrix<T, Rows, Colons>& Matrix<T, Rows, Colons>::operator*=(const T& value)
{
	for (SizeT i = 0; i < this->rows; i++)
		for (SizeT j = 0; j < this->colons; j++)
			this->_data[i][j] *= value;
	return *this;
}

template <typename T, uint32_t Rows, uint32_t Colons >
Matrix<T, Rows, Colons> Matrix<T, Rows, Colons>::operator/(const T& value)const
{
	Matrix<T, Rows, Colons> new_matrix = *this;
	for (SizeT i = 0; i < new_matrix.rows; i++)
		for (SizeT j = 0; j < new_matrix.colons; j++)
			new_matrix._data[i][j] /= value;
	return new_matrix;
}


template <typename T, uint32_t Rows, uint32_t Colons >
Matrix<T, Rows, Colons>& Matrix<T, Rows, Colons>::operator/=(const T& value)
{
	for (SizeT i = 0; i < this->rows; i++)
		for (SizeT j = 0; j < this->colons; j++)
			this->_data[i][j] /= value;
	return *this;
}

template <typename T, uint32_t Rows, uint32_t Colons >
Matrix<T, Rows, Colons> operator*(const T& value, const Matrix<T, Rows, Colons>& other)
{
	return other * value;
}



template <typename T, uint32_t Rows, uint32_t Colons >
Matrix<T, Rows, Colons> Matrix<T, Rows, Colons>::operator-()const
{
	Matrix<T, Rows, Colons> new_matrix;
	for (SizeT i = 0; i < new_matrix.rows; i++)
		for (SizeT j = 0; j < new_matrix.colons; j++)
			new_matrix._data[i][j] = -this->_data[i][j];
	return new_matrix;
}


template <typename T, uint32_t Rows, uint32_t Colons>
Matrix<T, Rows, Colons> Matrix<T, Rows, Colons>::operator~()const
{

	Matrix<T, Rows, Colons * 2> extention = this->extend();
	for (int i = 0; i < this->colons; i++)
	{
		if (extention._data[i][i] == 0)
		{
			bool broken = false;
			for (int j = i + 1; j < this->rows; j++)
				if (extention._data[j][i] != 0)
				{
					extention.swaprows(i, j);
					broken = true;
					break;
				}
			if (!broken)
				throw "determinant is 0";
		}

		for (SizeT j = i + 1; j < this->rows; j++)
			if (extention._data[j][i] != 0)
				extention.addrow(j, i, -extention._data[j][i] / extention._data[i][i]);
	}



	for (int i = this->colons - 1; i != 0; i--)
		for (int j = i - 1; ; j--)
			if (extention._data[i][i] != 0)
			{
				if (extention._data[j][i] != 0)
					extention.addrow(j, i, -extention._data[j][i] / extention._data[i][i]);
				if (j == 0)break;
			}
			else
			{
				throw "determinant is 0";
			}
	for (int i = 0; i < this->rows; i++)
		if (extention._data[i][i] == 0)
			throw "determinant is 0";
		else
			extention.multraw(i, T(1) / extention._data[i][i]);
	return extention.extract();
}

template<typename T, uint32_t Rows, uint32_t Colons>
inline const T& Matrix<T, Rows, Colons>::get(const SizeT& i, const SizeT& j) const
{
	return this->_data[i][j];
}

template<typename T, uint32_t Rows, uint32_t Colons>
inline void Matrix<T, Rows, Colons>::set(const SizeT& i, const SizeT& j, const T& value)
{
	this->_data[i][j] = value;
}

template <typename T, uint32_t Rows, uint32_t Colons >
void Matrix<T, Rows, Colons>::swaprows(const SizeT& row1, const SizeT& row2)
{
	for (SizeT i = 0; i < this->colons; i++)
	{
		T temp = this->_data[row1][i];
		this->_data[row1][i] = this->_data[row2][i];
		this->_data[row2][i] = temp;
	}
}

template <typename T, uint32_t Rows, uint32_t Colons >
Matrix<T, Rows, Colons / 2> Matrix<T, Rows, Colons>::extract()const
{
	Matrix<T, Rows, Colons / 2> newmat;
	for (SizeT i = 0; i < this->rows; i++)
	{
		for (SizeT j = newmat.colons; j < this->colons; j++)
			newmat._data[i][j - newmat.colons] = this->_data[i][j];
	}
	return newmat;
}


template <typename T, uint32_t Rows, uint32_t Colons >
void Matrix<T, Rows, Colons>::addrow(const int& targetrow, const int& addrow, const T& mult)
{
	for (SizeT j = 0; j < this->colons; j++)
		this->_data[targetrow][j] += this->_data[addrow][j] * mult;
}

template <typename T, uint32_t Rows, uint32_t Colons >
void Matrix<T, Rows, Colons>::multraw(const int& targetrow, const T& mult)
{
	for (int j = 0; j < this->colons; j++)
		this->_data[targetrow][j] *= mult;
}

template <typename T, uint32_t Rows, uint32_t Colons >
Matrix<T, Rows, Colons * 2> Matrix<T, Rows, Colons>::extend()const
{
	Matrix<T, Rows, Colons * 2> newmat;
	for (SizeT i = 0; i < this->rows; i++)
	{
		for (SizeT j = 0; j < this->colons; j++)
			newmat._data[i][j] = this->_data[i][j];

		for (SizeT j = this->colons; j < newmat.colons; j++)
			if (i == j - this->colons)
				newmat._data[i][j] = 1;
			else
				newmat._data[i][j] = 0;
	}
	return newmat;
}

template <typename T, uint32_t Rows, uint32_t Colons >
T Matrix<T, Rows, Colons>::olddet()const
{
	assert(Rows == Colons);
	if (this->rows == 1)
		return this->_data[0][0];

	if (this->colons == this->rows)
	{
		T result = 0;
		int one = -1;
		for (int i = 0; i < this->rows; i++)
			result += this->_data[i][0] * this->minor(i, 0).olddet() * (one *= -1);
		return result;
	}

}

template <typename T, uint32_t Rows, uint32_t Colons >
T Matrix<T, Rows, Colons>::det()const
{
	assert(Rows == Colons);

	Matrix<T, Rows, Colons * 2> extention = this->extend();
	for (int i = 0; i < this->colons; i++)
	{
		if (extention._data[i][i] == 0)
		{
			bool broken = false;
			for (int j = i + 1; j < this->rows; j++)
				if (extention._data[j][i] != 0)
				{
					extention.swaprows(i, j);
					broken = true;
					break;
				}
			if (!broken)
				return 0;
		}
		for (int j = i + 1; j < this->rows; j++)
			if (extention._data[j][i] != 0)
				extention.addrow(j, i, -extention._data[j][i] / extention._data[i][i]);
	}

	T res = 1;
	for (int i = 0; i < this->colons; i++)
		res *= extention._data[i][i];
	return res;

}

template <typename T, uint32_t Rows, uint32_t Colons >
T Matrix<T, Rows, Colons>::trace()const
{
	if (this->rows == this->colons)
	{
		T result = 0;
		for (int i = 0; i < this->rows; i++)
			result += this->_data[i][i];
		return result;
	}
	else
	{
		throw "In Matrix: error: unable to find trace of Matrix, matrix is not square";
	}
}

template <typename T, uint32_t Rows, uint32_t Colons >
Matrix<T, Rows - 1, Colons - 1> Matrix<T, Rows, Colons>::minor(const SizeT& row, const SizeT& colon)const
{
	Matrix<T, Rows - 1, Colons - 1> new_matrix;
	for (int i = 0, ni = 0; ni < new_matrix.rows; i++, ni++)
		for (int j = 0, nj = 0; nj < new_matrix.colons; j++, nj++)
		{
			if (row == i)
				i++;
			if (colon == j)
				j++;
			new_matrix.set(ni, nj, this->_data[i][j]);
		}
	return new_matrix;
}

template <typename T, uint32_t Rows, uint32_t Colons >
Matrix<T, Rows, Colons> Matrix<T, Rows, Colons>::transpose()const
{
	Matrix<T, Rows, Colons> new_matrix;
	for (int i = 0; i < new_matrix.rows; i++)
		for (int j = 0; j < new_matrix.colons; j++)
			new_matrix._data[i][j] = this->_data[j][i];
	return new_matrix;
}

template <typename T, uint32_t Rows, uint32_t Colons >
Matrix<T, Rows, Colons> Matrix<T, Rows, Colons>::adjugate()const
{
	Matrix<T, Rows, Colons> new_matrix;
	for (int i = 0; i < new_matrix.rows; i++)
		for (int j = 0; j < new_matrix.colons; j++)
			new_matrix._data[i][j] = this->minor(i, j).det() * (((i + j) & 1) ? -1 : 1);
	return new_matrix;
}

template <typename T, uint32_t Rows, uint32_t Colons >
Matrix<T, Rows, Colons> Matrix<T, Rows, Colons>::inverse()const
{
	if (this->det() != 0)
		return this->adjugate().transpose() / this->det();
	else
	{
		throw "In Matrix: error: unable to find inverse Matrix, determinant equals to 0";

	}
}

template <typename T, uint32_t Rows, uint32_t Colons >
bool Matrix<T, Rows, Colons>::operator==(const Matrix<T, Rows, Colons>& other)const
{
	if (this->rows == other.raws && this->colons == other.colons)
	{
		for (int i = 0; i < this->rows; i++)
			for (int j = 0; j < this->colons; j++)
				if (this->_data[i][j] != other._data[i][j])
					return false;
		return true;
	}
	else
		return false;
}

template <typename T, uint32_t Rows, uint32_t Colons >
bool Matrix<T, Rows, Colons>::operator!=(const Matrix<T, Rows, Colons>& other)const
{
	return !(*this == other);
}


//template<Appliable_to_matrix T>
//Matrix<T, Rows, Colons> one(const int& size)
//{
//	return Matrix<T, Rows, Colons>(size);
//}


template <typename T, uint32_t Rows, uint32_t Colons >
bool Matrix<T, Rows, Colons>::zero() const
{
	for (int i = 0; i < this->rows; i++)
		for (int j = 0; j < this->colons; j++)
			if (this->_data[i][j] != 0)
				return false;
	return true;
}

//template<Appliable_to_matrix T>
//Matrix<T, Rows, Colons> pow(const Matrix<T, Rows, Colons>& other, const uint32_t& n)
//{
//	Matrix<T, Rows, Colons> result(other.rows);
//	Matrix<T, Rows, Colons> buffer = other;
//	for (uint8_t i = 0; i < sizeof(n) * 8 && (1 << i) <= n; i++)
//	{
//		
//		if (n & (1 << i))
//			result *= buffer;
//		if ((1 << i) < n)
//			buffer *= buffer;
//	}
//	return result;
//}

template <typename T, uint32_t Rows, uint32_t Colons >
inline T& Matrix<T, Rows, Colons>::operator[](const Matrix<T, Rows, Colons>::_Indexer& indexer)
{
	return this->_data[indexer.i][indexer.j];
}

template <typename T, uint32_t Rows, uint32_t Colons >
inline const T& Matrix<T, Rows, Colons>::operator[](const Matrix<T, Rows, Colons> ::_Indexer& indexer) const
{
	return this->get(indexer.i, indexer.j);
}

