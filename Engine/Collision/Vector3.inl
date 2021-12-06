#pragma once
#include <math.h>

#include "Matrix4.h"
#include "Vector4.h"
namespace eae6320
{
	namespace Math
	{

		inline Vector3::Vector3(float i_x, float i_y, float i_z) :
			m_x(i_x),
			m_y(i_y),
			m_z(i_z)
		{
		}

		inline Vector3::Vector3(const Vector4 inVec) :
			m_x(inVec.x()),
			m_y(inVec.y()),
			m_z(inVec.z())
		{
		}
		
		inline Vector3::Vector3(const Vector3& i_other) :
			m_x(i_other.m_x),
			m_y(i_other.m_y),
			m_z(i_other.m_z)
		{
		}

		// operators
		inline Vector3& Vector3::operator=(const Vector3& i_other)
		{
			m_x = i_other.m_x;
			m_y = i_other.m_y;
			m_z = i_other.m_z;
		
			return *this;
		}

		// accessors
		inline float Vector3::x(void) const
		{
			return m_x;
		}

		inline float Vector3::y(void) const
		{
			return m_y;
		}
		inline float Vector3::z(void) const
		{
			return m_z;
		}
		

		inline void Vector3::x(float i_x)
		{
			m_x = i_x;
		}

		inline void Vector3::y(float i_y)
		{
			m_y = i_y;
		}
		inline void Vector3::z(float i_z)
		{
			m_z = i_z;
		}
		

		inline Vector3& Vector3::operator+=(const Vector3& i_other)
		{
			m_x += i_other.m_x;
			m_y += i_other.m_y;
			m_z += i_other.m_z;
			
			return *this;
		}

		inline Vector3& Vector3::operator-=(const Vector3& i_other)
		{
			m_x -= i_other.m_x;
			m_y -= i_other.m_y;
			m_z -= i_other.m_z;
			
			return *this;
		}

		inline Vector3& Vector3::operator*=(const Vector3& i_other)
		{
			m_x *= i_other.m_x;
			m_y *= i_other.m_y;
			m_z *= i_other.m_z;
			
			return *this;
		}

		inline Vector3& Vector3::operator*=(float i_other)
		{
			m_x *= i_other;
			m_y *= i_other;
			m_z *= i_other;
			
			return *this;
		}

		inline Vector3& Vector3::operator/=(const Vector3& i_other)
		{
			m_x /= i_other.m_x;
			m_y /= i_other.m_y;
			m_z /= i_other.m_z;
			
			return *this;
		}

		inline Vector3& Vector3::operator/=(float i_other)
		{
			m_x /= i_other;
			m_y /= i_other;
			m_z /= i_other;
		
			return *this;
		}
		inline Vector3 Vector3::operator-(void)
		{
			return Vector3(-m_x, -m_y, -m_z);
		}

		inline float Vector3::LengthSq() const
		{
			return (m_x * m_x) + (m_y * m_y) + (m_z * m_z) ;
		}

		inline float Vector3::Length() const
		{
			return static_cast<float>(sqrt(LengthSq()));
		}

		inline Vector3& Vector3::Normalize()
		{
			*this = Normalized();

			return *this;
		}

		// stand alone operators
		inline Vector3 operator+(const Vector3& i_lhs, const Vector3& i_rhs)
		{
			return Vector3(i_lhs.x() + i_rhs.x(), i_lhs.y() + i_rhs.y(), i_lhs.z() + i_rhs.z());
		}

		inline Vector3 operator-(const Vector3& i_lhs, const Vector3& i_rhs)
		{
			return Vector3(i_lhs.x() - i_rhs.x(), i_lhs.y() - i_rhs.y(), i_lhs.z() - i_rhs.z());
		}

		inline Vector3 operator*(const Vector3& i_lhs, const Vector3& i_rhs)
		{
			return Vector3(i_lhs.x() * i_rhs.x(), i_lhs.y() * i_rhs.x(), i_lhs.z() * i_rhs.z());
		}

		inline Vector3 operator*(const Vector3& i_lhs, float i_rhs)
		{
			return Vector3(i_lhs.x() * i_rhs, i_lhs.y() * i_rhs, i_lhs.z() * i_rhs);
		}

		inline Vector3 operator*(float i_lhs, const Vector3& i_rhs)
		{
			return Vector3(i_lhs * i_rhs.x(), i_lhs * i_rhs.y(), i_lhs * i_rhs.z());
		}

		inline Vector3 operator/(const Vector3& i_lhs, const Vector3& i_rhs)
		{
			return Vector3(i_lhs.x() / i_rhs.x(), i_lhs.y() / i_rhs.y(), i_rhs.z() / i_lhs.z());
		}

		inline Vector3 operator/(const Vector3& i_lhs, float i_rhs)
		{
			return Vector3(i_lhs.x() / i_rhs, i_lhs.y() / i_rhs, i_lhs.z() / i_rhs);
		}

		inline bool operator==(const Vector3& i_lhs, const Vector3& i_rhs)
		{
			return (i_lhs.x() == i_rhs.x()) && (i_lhs.y() == i_rhs.y()) && (i_lhs.z() == i_rhs.z()) ;
		}

		inline bool operator!=(const Vector3& i_lhs, const Vector3& i_rhs)
		{
			return !operator==(i_lhs, i_rhs);
		}

		inline float dot(const Vector3& i_lhs, const Vector3& i_rhs)
		{
			return i_lhs.x() * i_rhs.x() + i_lhs.y() * i_rhs.y() + i_lhs.z() * i_rhs.z() ;
		}







		















	} // namespace Math
} // namespace Engine