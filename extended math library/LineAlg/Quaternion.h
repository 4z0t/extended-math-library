#pragma once
#include "Vector3.h"
template<typename T>
class Quaternion
{

public:
	T x, y, z, w;

	Quaternion() :x(), y(), z(), w() {};
	Quaternion(const T& x, const Vector3<T>v) :x(x), y(v.x), z(v.y), w(v.z) {};
	Quaternion(const T& x, const T& y, const T& z, const T& w) :x(x), y(y), z(z), w(w) {};
	Quaternion(const Quaternion& other) : x(other.x), y(other.y), z(other.z), w(other.w) {};


	Quaternion& operator=(const Quaternion& other);
	Quaternion operator+(const Quaternion& other)const;
	Quaternion operator-(const Quaternion& other)const;
	Quaternion operator*(const Quaternion& other)const;
	Quaternion operator*(const T& value)const;
	Quaternion operator/(const T& value)const;
	Quaternion operator~()const;


	Quaternion& operator+=(const Quaternion& other);
	Quaternion& operator-=(const Quaternion& other);


	Quaternion operator-()const;

	Vector3<T> get_complex_vector()const;

	friend Quaternion conj(const Quaternion& q);
	friend T norm(const Quaternion& q);
};
template<typename T>
Quaternion<T> conj(const Quaternion<T>& q);
