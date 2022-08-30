#pragma once


template<typename T>
class Vector3
{

public:
	T x, y, z;

	Vector3() :x(), y(), z() {};
	Vector3(const T& x, const T& y, const T& z) :x(x), y(y), z(z) {};
	Vector3(const Vector3& other) :x(other.x), y(other.y), z(other.z) {};


	Vector3& operator=(const Vector3& other);
	Vector3 operator+(const Vector3& other)const;
	Vector3 operator-(const Vector3& other)const;
	Vector3 operator*(const T& value)const;
	Vector3 operator/(const T& value)const;


	Vector3& operator+=(const Vector3& other);
	Vector3& operator-=(const Vector3& other);

	Vector3 operator-()const;


	friend Vector3 normal(const Vector3& vec);
	friend T norm(const Vector3& vec);
	friend T dot(const Vector3& first, const Vector3& second);
	friend Vector3 cross(const Vector3& first, const Vector3& second);

};
template<typename T>
Vector3<T> normal(const Vector3<T>& vec);

template<typename T>
T norm(const Vector3<T>& vec);

template<typename T>
T dot(const Vector3<T>& first, const Vector3<T>& second);

template<typename T>
Vector3<T> cross(const Vector3<T>& first, const Vector3<T>& second);