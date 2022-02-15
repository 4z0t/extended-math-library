#pragma once
template<typename T>
class Vector3
{

	//public:
		T x, y, z;

	public:
		Vector3() :x(0), y(0), z(0) {}
		Vector3(const T& x, const T& y, const T& z);
		Vector3(const Vector3& other);


		Vector3& operator=(const Vector3& other);
		Vector3 operator+(const Vector3& other);
		Vector3 operator-(const Vector3& other);
		Vector3 operator*(const T& value);
		Vector3 operator/(const T& value);


		Vector3& operator+=(const Vector3& other);
		Vector3& operator-=(const Vector3& other);

		Vector3 operator-();


		/*Vector3 operator+(const Vector3& other)const;
		Vector3 operator-(const Vector3& other)const;
		Vector3 operator*(const T& value)const;
		Vector3 operator/(const T& value)const;*/

		/*Vector3& xyz(const Vector3& other);
		Vector3 xyz();
		Vector3 xyz()const;*/
		friend Vector3 normal(const Vector3& vec);
		friend T norm(const Vector3& vec);
		friend T dot(const Vector3& first, const Vector3& second);
		friend Vector3 cross(const Vector3& first, const Vector3& second);
		//Vector3 operator+(const Vector3& other);

		
		/*friend Vector3 abs(const Vector3& vec);
		friend Vector3 max(const Vector3& vec, const T& value);
		friend Vector3 min(const Vector3& vec, const T& value);
		friend Vector3 sign(const Vector3& vec);
		friend Vector3 fmod(const Vector3& vec, const T& value);
		friend Vector3 clamp(const Vector3& vec, const T& minv, const T& maxv);*/

};

