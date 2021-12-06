#include <math.h>

#include "Matrix4.h"
#include "Vector3.h"

namespace eae6320
{
	namespace Math
	{

		inline Vector4::Vector4(float i_x, float i_y,float i_z, float i_w) :
			m_x(i_x),
			m_y(i_y),
			m_z(i_z),
			m_w(i_w)
		{
		}
		inline Vector4::Vector4(float i_x, float i_y, float i_z) :
			m_x(i_x),
			m_y(i_y),
			m_z(i_z),
			m_w(1.0f)
		{
		}
		inline Vector4::Vector4(const Vector4& i_other) :
			m_x(i_other.m_x),
			m_y(i_other.m_y),
			m_z(i_other.m_z),
			m_w(i_other.m_w)
		{
		}

		inline Vector4::Vector4(const Vector3& inVec3):
			m_x(inVec3.x()),
			m_y(inVec3.y()),
			m_z(inVec3.z()),
			m_w(1)
		
		{
			
		}
		inline Vector4::Vector4(const Vector3& inVec3,float i_val) :
			m_x(inVec3.x()),
			m_y(inVec3.y()),
			m_z(inVec3.z()),
			m_w(i_val)

		{

		}

		
		// operators
		inline Vector4& Vector4::operator=(const Vector4& i_other)
		{
			m_x = i_other.m_x;
			m_y = i_other.m_y;
			m_z = i_other.m_z;
			m_w = i_other.m_w;
			return *this;
		}

		// accessors
		inline float Vector4::x(void) const
		{
			return m_x;
		}

		inline float Vector4::y(void) const
		{
			return m_y;
		}
		inline float Vector4::z(void) const
		{
			return m_z;
		}
		inline float Vector4::w(void) const
		{
			return m_w;
		}
		
		inline void Vector4::x(float i_x)
		{
			m_x = i_x;
		}

		inline void Vector4::y(float i_y)
		{
			m_y = i_y;
		}
		inline void Vector4::z(float i_z)
		{
			m_z = i_z;
		}
		inline void Vector4::w(float i_w)
		{
			m_w = i_w;
		}
		
		inline Vector4& Vector4::operator+=(const Vector4& i_other)
		{
			m_x += i_other.m_x;
			m_y += i_other.m_y;
			m_z += i_other.m_z;
			m_w += i_other.m_w;
			return *this;
		}

		inline Vector4& Vector4::operator-=(const Vector4& i_other)
		{
			m_x -= i_other.m_x;
			m_y -= i_other.m_y;
			m_z -= i_other.m_z;
			m_w -= i_other.m_w;
			return *this;
		}

		inline Vector4& Vector4::operator*=(const Vector4& i_other)
		{
			m_x *= i_other.m_x;
			m_y *= i_other.m_y;
			m_z *= i_other.m_z;
			m_w *= i_other.m_w;
			return *this;
		}

		inline Vector4& Vector4::operator*=(float i_other)
		{
			m_x *= i_other;
			m_y *= i_other;
			m_z *= i_other;
			m_w *= i_other;
			return *this;
		}

		inline Vector4& Vector4::operator/=(const Vector4& i_other)
		{
			m_x /= i_other.m_x;
			m_y /= i_other.m_y;
			m_z /= i_other.m_z;
			m_w /= i_other.m_w;
			return *this;
		}

		inline Vector4& Vector4::operator/=(float i_other)
		{
			m_x /= i_other;
			m_y /= i_other;
			m_z /= i_other;
			m_w /= i_other;
			return *this;
		}
		inline Vector4 Vector4::operator-(void)
		{
			return Vector4(-m_x, -m_y, -m_z, -m_w);
		}

		inline float Vector4::LengthSq() const
		{
			return (m_x * m_x) + (m_y * m_y) + (m_z*m_z) +(m_w*m_w);
		}

		inline float Vector4::Length() const
		{
			return static_cast<float>(sqrt(LengthSq()));
		}

		inline Vector4& Vector4::Normalize()
		{
			*this = Normalized();

			return *this;
		}

		// stand alone operators
		inline Vector4 operator+(const Vector4& i_lhs, const Vector4& i_rhs)
		{
			return Vector4(i_lhs.x() + i_rhs.x(), i_lhs.y() + i_rhs.y(), i_lhs.z() + i_rhs.z(), i_lhs.w()+i_rhs.w());
		}

		inline Vector4 operator-(const Vector4& i_lhs, const Vector4& i_rhs)
		{
			return Vector4(i_lhs.x() - i_rhs.x(), i_lhs.y() - i_rhs.y(), i_lhs.z() - i_rhs.z(), i_lhs.w() - i_rhs.w());
		}

		inline Vector4 operator*(const Vector4& i_lhs, const Vector4& i_rhs)
		{
			return Vector4(i_lhs.x() * i_rhs.x(), i_lhs.y() * i_rhs.x(),i_lhs.z() * i_rhs.z(), i_lhs.w() * i_rhs.w());
		}

		inline Vector4 operator*(const Vector4& i_lhs, float i_rhs)
		{
			return Vector4(i_lhs.x() * i_rhs, i_lhs.y() * i_rhs,i_lhs.z()*i_rhs, i_lhs.w() *i_rhs);
		}

		inline Vector4 operator*(float i_lhs, const Vector4& i_rhs)
		{
			return Vector4(i_lhs * i_rhs.x(), i_lhs * i_rhs.y(), i_lhs * i_rhs.z(), i_lhs * i_rhs.w());
		}

		inline Vector4 operator/(const Vector4& i_lhs, const Vector4& i_rhs)
		{
			return Vector4(i_lhs.x() / i_rhs.x(), i_lhs.y() / i_rhs.y(), i_rhs.z()/i_lhs.z(), i_rhs.w() / i_rhs.w());
		}

		inline Vector4 operator/(const Vector4& i_lhs, float i_rhs)
		{
			return Vector4(i_lhs.x() / i_rhs, i_lhs.y() / i_rhs, i_lhs.z()/i_rhs, i_lhs.w() / i_rhs);
		}

		inline bool operator==(const Vector4& i_lhs, const Vector4& i_rhs)
		{
			return (i_lhs.x() == i_rhs.x()) && (i_lhs.y() == i_rhs.y()) && (i_lhs.z() == i_rhs.z()) && (i_lhs.w() == i_rhs.w());
		}

		inline bool operator!=(const Vector4& i_lhs, const Vector4& i_rhs)
		{
			return !operator==(i_lhs, i_rhs);
		}

		inline float dot(const Vector4& i_lhs, const Vector4& i_rhs)
		{
			return i_lhs.x() * i_rhs.x() + i_lhs.y() * i_rhs.y() + i_lhs.z()*i_rhs.z() + i_lhs.w()*i_rhs.w();
		}






/*
		inline Vector4 operator*(const Matrix4& i_mtx, const Vector4& i_vec)
		{
			Vector4 NewVec;
			

			
			NewVec.x( dot(i_vec, i_mtx.GetRow(0)));
			NewVec.y(dot(i_vec, i_mtx.GetRow(1)));
			NewVec.z(dot(i_vec, i_mtx.GetRow(2)));
			NewVec.w(dot(i_vec, i_mtx.GetRow(3)));
			return NewVec;
		}
		
		inline Vector4 operator*(const Vector4& i_vec, const Matrix4& i_mtx)
		{
			Vector4 NewVec;
			


			NewVec.x(dot(i_vec, i_mtx.GetRow(0)));
			NewVec.y(dot(i_vec, i_mtx.GetRow(1)));
			NewVec.z(dot(i_vec, i_mtx.GetRow(2)));
			NewVec.w(dot(i_vec, i_mtx.GetRow(3)));
			return NewVec;
		}
		*/



		inline Vector4 operator-(const Vector4& i_lhs, float i_rhs)
		{
			return Vector4(i_lhs.x() - i_rhs, i_lhs.y() - i_rhs, i_lhs.z() - i_rhs, i_lhs.w() - i_rhs);
		}
		inline Vector4 operator-(float i_lhs, const Vector4& i_rhs)
		{
			return Vector4(i_rhs.x() - i_lhs, i_rhs.y() - i_lhs, i_rhs.z() - i_lhs, i_rhs.w() - i_lhs);
		}

		inline Vector4 operator+(const Vector4& i_lhs, float i_rhs)
		{
			return Vector4(i_lhs.x() + i_rhs, i_lhs.y() + i_rhs, i_lhs.z() + i_rhs, i_lhs.w() + i_rhs);
		}
		inline Vector4 operator+(float i_lhs, const Vector4& i_rhs)
		{
			return Vector4(i_rhs.x() + i_lhs, i_rhs.y() + i_lhs, i_rhs.z() + i_lhs, i_rhs.w() + i_lhs);
		}







		
	} // namespace Math
} // namespace Engine