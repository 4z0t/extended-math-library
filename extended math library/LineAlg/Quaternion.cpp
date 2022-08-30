#include "Quaternion.h"


template<typename T>
Quaternion<T>& Quaternion<T>::operator=(const Quaternion& other)
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
	this->w = other.w;
	return *this;
}

template<typename T>
inline Quaternion<T> Quaternion<T>::operator+(const Quaternion& other)const
{
	return Quaternion<T>(this->x + other.x, this->y + other.y, this->z + other.z, this->w + other.w);
}

template<typename T>
inline Quaternion<T> Quaternion<T>::operator-(const Quaternion& other)const
{
	return Quaternion<T>(this->x - other.x, this->y - other.y, this->z - other.z, this->w - other.w);
}

template<typename T>
Quaternion<T> Quaternion<T>::operator*(const Quaternion& other) const
{
	Vector3<T> v1 = this->get_complex_vector();
	Vector3<T> v2 = other.get_complex_vector();
	Vector3<T> ijk_cross = cross(v1, v2);
	T ijk_dot = dot(v1, v2);

	return Quaternion<T>(this->x * other.x - ijk_dot, ijk_cross + this->x * v2 + other.x * v1);
}

template<typename T>
inline Quaternion<T> Quaternion<T>::operator*(const T& value)const
{
	return Quaternion<T>(this->x * value, this->y * value, this->z * value, this->w * value);
}

template<typename T>
inline Quaternion<T> Quaternion<T>::operator/(const T& value)const
{
	return Quaternion(this->x / value, this->y / value, this->z / value, this->w / value);
}

template<typename T>
inline Quaternion<T> Quaternion<T>::operator~() const
{
	return Quaternion<T>(this->x, -this->y, -this->z, -this->w);
}

template<typename T>
inline Quaternion<T> conj(const Quaternion<T>& q)
{
	return ~q;
}

template<typename T>
inline T norm(const Quaternion<T>& q)
{
	return sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
}

template<typename T>
Quaternion<T>& Quaternion<T>::operator+=(const Quaternion& other)
{
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
	this->w += other.w;
	return *this;
}

template<typename T>
Quaternion<T>& Quaternion<T>::operator-=(const Quaternion& other)
{
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;
	this->w -= other.w;
	return *this;
}

template<typename T>
inline Quaternion<T> Quaternion<T>::operator-()const
{
	return Quaternion<T>(-this->x, -this->y, -this->z, -this->w);
}

template<typename T>
Vector3<T> Quaternion<T>::get_complex_vector() const
{
	return Vector3<T>(y, z, w);
}


