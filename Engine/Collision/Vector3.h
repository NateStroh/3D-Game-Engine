#pragma once
namespace eae6320
{
	namespace Math
	{
		class Matrix4;
		class Vector4;
		class Vector3
		{

		public:
			Vector3() {
				m_x = 0;
				m_y = 0;
				m_z = 0;
			}
			// standard constructor
			inline Vector3(float i_x, float i_y, float i_z);
			inline Vector3(const Vector4 inVec);
			// copy constructor - for completeness
			inline Vector3(const Vector3& i_other);
			// assignment operator
			inline Vector3& operator=(const Vector3& i_rhs);

			// element accessors
			// - get individual element
			inline float x(void) const;
			inline float y(void) const;
			inline float z(void) const;
			
			// - set individual element
			inline void x(float i_x);
			inline void y(float i_y);
			inline void z(float i_z);
			
			// modifying operators
			inline Vector3& operator+=(const Vector3& i_rhs);
			inline Vector3& operator-=(const Vector3& i_rhs);

			inline Vector3& operator*=(const Vector3& i_other);
			inline Vector3& operator*=(float i_val);

			inline Vector3& operator/=(const Vector3& i_other);
			inline Vector3& operator/=(float i_val);

			// negate
			inline Vector3 operator-(void);

			inline Vector3& Normalize();
			inline Vector3 Normalized() const;

			inline float Length() const;
			inline float LengthSq() const;



			// - ( 0.0f, 0.0f, 0.0f )
			static const Vector3 Zero;

		private:
			float	m_x, m_y, m_z;
		};

		inline Vector3 Normalized(const Vector3& i_vec);

		inline Vector3 operator+(const Vector3& i_lhs, const Vector3& i_rhs);
		inline Vector3 operator-(const Vector3& i_lhs, const Vector3& i_rhs);

		inline Vector3 operator*(const Vector3& i_lhs, float i_rhs);


		inline Vector3 operator/(const Vector3& i_lhs, const Vector3& i_rhs);
		inline Vector3 operator/(const Vector3& i_lhs, float i_rhs);

		inline bool operator==(const Vector3& i_lhs, const Vector3& i_rhs);
		inline bool operator!=(const Vector3& i_lhs, const Vector3& i_rhs);

		inline float dot(const Vector3& i_lhs, const Vector3& i_rhs);


		//inline Vector3 operator*(const Matrix4& i_mtx, const Vector3& i_vec);
		//inline Vector3 operator*(const Vector3& i_vec, const Matrix4& i_mtx);







	};


}

#include "Vector3.inl"