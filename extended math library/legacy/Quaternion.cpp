//#include "Quaternion.h"
//
//
//
//std::partial_ordering Quaternion::operator <=> (const Quaternion& q) const
//{
//	if (this->get_im_i() != 0 || q.get_im_i() != 0 ||
//		this->get_im_j() != 0 || q.get_im_j() != 0 ||
//		this->get_im_k() != 0 || q.get_im_k() != 0)
//		return std::partial_ordering::unordered;
//
//	return this->get_real() <=> q.get_real();
//}
//
//
//Quaternion conj(const Quaternion& q)
//{
//	return Quaternion(conj(q.get_first()), -q.get_second());
//}
//
//Quaternion operator+(const double& right, const Quaternion& left)
//{
//	return Quaternion(right) + left;
//}
//Quaternion operator*(const double& right, const Quaternion& left)
//{
//	return Quaternion(right) * left;
//
//}
//Quaternion operator-(const double& right, const Quaternion& left)
//{
//	return Quaternion(right) - left;
//}
//
//
//std::ostream& operator << (std::ostream& out, const Quaternion& q)
//{
//	double buffer;
//	bool was_prev = false;
//	bool is_prev = true;
//	if (is_prev = (buffer = q.get_real()) != 0)
//		out << buffer;
//	if (was_prev = is_prev /*=*/ || was_prev; is_prev = (buffer = q.get_im_i()) != 0)
//		out << ((was_prev && buffer > 0) ? " +" : " ") << buffer << 'i';
//	if (was_prev = is_prev /*=*/ || was_prev; is_prev = (buffer = q.get_im_j()) != 0)
//		out << ((was_prev && buffer > 0) ? " +" : " ") << buffer << 'j';
//	if (was_prev = is_prev /*=*/ || was_prev; is_prev = (buffer = q.get_im_k()) != 0)
//		out << ((was_prev && buffer > 0) ? " +" : " ") << buffer << 'k';
//	return out;
//}
//
//Quaternion::operator std::string()const
//{
//	std::string out = "";
//	double buffer;
//	bool was_prev = false;
//	bool is_prev = true;
//	if (is_prev = (buffer = this->get_real()) != 0)
//		(out += ((buffer > 0) ? "+" : "")) += std::to_string(buffer);
//	if (was_prev = is_prev /*=*/ || was_prev; is_prev = (buffer = this->get_im_i()) != 0)
//		((out += ((buffer > 0) ? "+" : "")) += std::to_string(buffer)) += 'i';
//	if (was_prev = is_prev /*=*/ || was_prev; is_prev = (buffer = this->get_im_j()) != 0)
//		((out += ((buffer > 0) ? "+" : "")) += std::to_string(buffer)) += 'j';
//	if (was_prev = is_prev /*=*/ || was_prev; is_prev = (buffer = this->get_im_k()) != 0)
//		((out += ((buffer > 0) ? "+" : "")) += std::to_string(buffer)) += 'k';
//	out.erase(std::remove_if(out.begin(), out.end(), std::isspace), out.end());
//	return out;
//}
//
//
////Quaternion operator""i(long double val)
////{
////	return Quaternion(0, val);
////}
//Quaternion operator""j(long double val)
//{
//	return Quaternion(0, 0, val);
//}
//Quaternion operator""k(long double val)
//{
//	return Quaternion(0, 0, 0, val);
//}
//
////Quaternion operator""i(unsigned long long int val)
////{
////	return Quaternion(0, val);
////}
//Quaternion operator""j(unsigned long long int val)
//{
//	return Quaternion(0, 0, val);
//}
//Quaternion operator""k(unsigned long long int val)
//{
//	return Quaternion(0, 0, 0, val);
//}