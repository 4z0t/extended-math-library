#include "Vector3.h"

template<typename T>
Vector3<T>::Vector3(const T& x, const T& y, const T& z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

template<typename T>
inline Vector3<T>::Vector3(const Vector3& other)
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
}

template<typename T>
Vector3<T> & Vector3<T>::operator=(const Vector3& other)
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
	return *this;
}

template<typename T>
Vector3<T> Vector3<T>::operator+(const Vector3& other)
{
	return Vector3<T>(this->x + other.x, this->y + other.y, this->z + other.z);
}

template<typename T>
Vector3<T> Vector3<T>::operator-(const Vector3& other)
{
	return Vector3<T>(this->x - other.x, this->y - other.y, this->z - other.z);
}

template<typename T>
Vector3<T> Vector3<T>::operator*(const T& value)
{
	return Vector3<T>(this->x * value, this->y * value, this->z * value);
}

template<typename T>
Vector3<T> Vector3<T>::operator/(const T& value)
{
	return Vector3(this->x / value, this->y / value, this->z / value);
}

template<typename T>
Vector3<T>& Vector3<T>::operator+=(const Vector3& other)
{
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
	return *this;
}

template<typename T>
Vector3<T>& Vector3<T>::operator-=(const Vector3& other)
{
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;
	return *this;
}

template<typename T>
Vector3<T> Vector3<T>::operator-()
{
	return Vector3<T>(-this->x, -this->y, -this->z);
}

template<typename T>
Vector3<T> normal(const Vector3<T>& vec)
{
	return vec / norm(vec);
}

template<typename T>
T norm(const Vector3<T> & vec)
{
	return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

template<typename T>
T dot(const Vector3<T>& first, const Vector3<T>& second)
{
	return first.x * second.x + first.y * second.y + first.z * second.z;
}

template<typename T>
Vector3<T> cross(const Vector3<T>& first, const Vector3<T>& second)
{
	return Vector3<T>(first.y * second.z - first.z * second.y,
		first.z * second.x - first.x * second.z,
		first.x * second.y - first.y * second.x);
}

