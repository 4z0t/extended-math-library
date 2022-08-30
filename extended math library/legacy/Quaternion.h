//#pragma once
//
//
//
//class Quaternion
//{
//public:
//	class Im_i;
//	class Im_j;
//	class Im_k;
//	class Im_i
//	{
//		friend Im_j;
//		friend Im_k;
//		double i;
//	public:
//		Im_i() :i(0) {};
//		Im_i(const double& val) :i(val) {};
//
//		~Im_i();
//
//		Im_i operator* (const double& val)//i*1
//		{
//			return this->i * val;
//		}
//		Im_i operator* (const Im_i& val)//i*i = -1
//		{
//			return -this->i * val.i;
//		}
//		Im_k operator* (const Im_j& val)//i*j = k
//		{
//			return this->i * val.j;
//		}
//		Im_j operator* (const Im_k& val)//i*k = -j
//		{
//			return -this->i * val.k;
//		}
//	private:
//
//	};
//	class Im_j
//	{
//		friend Im_i;
//		friend Im_k;
//		double j;
//	public:
//		Im_j() :j(0) {};
//		Im_j(const double& val) :j(val) {};
//		~Im_j();
//
//		Im_i operator* (const double& val)//j*1
//		{
//			return this->j * val;
//		}
//		Im_k operator* (const Im_i& val)//j*i = -k
//		{
//			return -this->j * val.i;
//		}
//		Im_j operator* (const Im_j& val)//j*j = -1
//		{
//			return -this->j * val.j;
//		}
//		Im_i operator* (const Im_k& val)//j*k = i
//		{
//			return this->j * val.k;
//		}
//
//	private:
//
//	};
//	class Im_k
//	{
//		friend Im_i;
//		friend Im_j;
//		double k;
//	public:
//		Im_k() :k(0) {};
//		Im_k(const double& val) :k(val) {};
//		~Im_k();
//		Im_i operator* (const double& val)//k*1
//		{
//			return this->k * val;
//		}
//		Im_j operator* (const Im_i& val)//k*i = j
//		{
//			return this->k * val.i;
//		}
//		Im_i operator* (const Im_j& val)//k*j = -i
//		{
//			return -this->k * val.j;
//		}
//		Im_i operator* (const Im_k& val)//k*k = -1
//		{
//			return -this->k * val.k;
//		}
//	private:
//
//	};
//
//
//
//
//private:
//	double a;
//	Im_i b;
//	Im_j c;
//	Im_k d;
//
//
//
//
//
//
//};
//
//
//Quaternion::Im_i operator ""i(long double val)
//{
//
//}
//
//Quaternion::Im_j operator ""j(long double val)
//{
//
//}
//
//Quaternion::Im_k operator ""k(long double val)
//{
//
//}
//
//
//Quaternion::Im_i::Im_i()
//{
//}
//
//Quaternion::Im_i::~Im_i()
//{
//}
//
//Quaternion::Im_j::Im_j()
//{
//}
//
//Quaternion::Im_j::~Im_j()
//{
//}
//
//Quaternion::Im_k::Im_k()
//{
//}
//
//Quaternion::Im_k::~Im_k()
//{
//}

//#include <complex>
//#include <iostream>
//#include <compare>
//#include<algorithm>
//#include <string>
//
//typedef std::complex<double> _cmpd;
//class Quaternion
//{
//	typedef std::complex<_cmpd> _quat;
//	_quat val;
//public:
//	Quaternion() :val(_cmpd(0, 0), _cmpd(0, 0)) {}
//	Quaternion(const double& a, const double& b = 0, const double& c = 0, const double& d = 0) :val(_cmpd(a, b), _cmpd(c, d)) {}
//	Quaternion(_quat val) :val(val) {}
//	Quaternion(_cmpd re, _cmpd im = 0) :val(re, im) {}
//
//	Quaternion& operator=(const Quaternion& other)
//	{
//		this->val = other.val;
//		return *this;
//	}
//
//	inline _cmpd get_first()const { return this->val.real(); }
//	inline _cmpd get_second()const { return this->val.imag(); }
//	inline double get_real()const { return this->val.real().real(); }
//	inline double get_im_i()const { return this->val.real().imag(); }
//	inline double get_im_j()const { return this->val.imag().real(); }
//	inline double get_im_k()const { return this->val.imag().imag(); }
//	
	/*_cmpd to_complex()const
	{
		return val.real();
	}*/
//	operator _cmpd()
//	{
//		return val.real();
//	}
//
//	operator double ()
//	{
//	return val.real().real();
//	}
//
//	inline Quaternion operator+(const Quaternion& other)const
//	{
//		return this->val + other.val;
//	}
//	inline Quaternion operator+=(const Quaternion& other)
//	{
//		this->val = this->val + other.val;
//		return *this;
//	}
//	inline Quaternion operator-=(const Quaternion& other)
//	{
//		 this->val = this->val - other.val;
//		 return *this;
//	}
//
//	inline Quaternion operator*=(const Quaternion& other)
//	{
//		this->val = this->val * other.val;
//		return *this;
//	}
//	inline Quaternion operator*(const Quaternion& other)const
//	{
//		return Quaternion(this->val.real() * other.val.real() - conj(other.val.imag()) * this->val.imag(),
//			other.val.imag() * this->val.real() + this->val.imag() * conj(other.val.real()));
//	}
//	inline Quaternion operator-(const Quaternion& other)const
//	{
//		return this->val - other.val;
//	}
//	inline Quaternion operator-()const
//	{
//		return -this->val;
//	}
//
//	  operator std::string()const;
//	
//
//
//	std::partial_ordering operator <=> (const Quaternion& q) const;
//
//
//};
//std::ostream& operator << (std::ostream& out, const Quaternion& q);

//Quaternion conj(const Quaternion& q);
//
//Quaternion operator+(const double& right, const Quaternion& left);
//Quaternion operator*(const double& right, const Quaternion& left);
//Quaternion operator-(const double& right, const Quaternion& left);
//
//Quaternion operator""j(long double val);
//Quaternion operator""k(long double val);
//Quaternion operator""j(unsigned long long int val);
//Quaternion operator""k(unsigned long long int val);
