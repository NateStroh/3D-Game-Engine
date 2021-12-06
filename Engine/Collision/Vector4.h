#pragma once




namespace eae6320
{
	namespace Math
	{
		class Matrix4;
		class Vector3;

		
		class Vector4
		{

		public:
			Vector4() {
				m_x = 0;
				m_y = 0;
				m_z = 0;
				m_w = 0;
			}
			// standard constructor
			inline Vector4(float i_x, float i_y, float i_z);
			inline Vector4(float i_x, float i_y, float i_z, float i_w);
			inline Vector4(const Vector3& inVec3);
			inline Vector4(const Vector3& inVec3,float i_val);
			// copy constructor - for completeness
			inline Vector4(const Vector4& i_other);
			// assignment operator
			inline Vector4& operator=(const Vector4& i_rhs);

			// element accessors
			// - get individual element
			inline float x(void) const;
			inline float y(void) const;
			inline float z(void) const;
			inline float w(void) const;
			// - set individual element
			inline void x(float i_x);
			inline void y(float i_y);
			inline void z(float i_z);
			inline void w(float i_w);
			// modifying operators
			inline Vector4& operator+=(const Vector4& i_rhs);
			inline Vector4& operator-=(const Vector4& i_rhs);

			inline Vector4& operator*=(const Vector4& i_other);
			inline Vector4& operator*=(float i_val);

			inline Vector4& operator/=(const Vector4& i_other);
			inline Vector4& operator/=(float i_val);

			// negate
			inline Vector4 operator-(void);

			inline Vector4& Normalize();
			inline Vector4 Normalized() const;

			inline float Length() const;
			inline float LengthSq() const;



			
	











			
			// - ( 0.0f, 0.0f, 0.0f )
			static const Vector4 Zero;

		private:
			float	m_x, m_y, m_z, m_w;
		};

		inline Vector4 Normalized(const Vector4& i_vec);

		inline Vector4 operator+(const Vector4& i_lhs, const Vector4& i_rhs);
		inline Vector4 operator-(const Vector4& i_lhs, const Vector4& i_rhs);

		//Vector3 minus floats
		inline Vector4 operator-(const Vector4& i_lhs, float i_rhs);
		inline Vector4 operator-(float i_lhs, const Vector4& i_rhs);
		//Vector4 plus floats
		inline Vector4 operator+(const Vector4& i_lhs, float i_rhs);
		inline Vector4 operator+(float i_lhs, const Vector4& i_rhs);

		inline Vector4 operator*(const Vector4& i_lhs, float i_rhs);


		inline Vector4 operator/(const Vector4& i_lhs, const Vector4& i_rhs);
		inline Vector4 operator/(const Vector4& i_lhs, float i_rhs);

		inline bool operator==(const Vector4& i_lhs, const Vector4& i_rhs);
		inline bool operator!=(const Vector4& i_lhs, const Vector4& i_rhs);

		inline float dot(const Vector4& i_lhs, const Vector4& i_rhs);


		//inline Vector4 operator*(const Matrix4& i_mtx, const Vector4& i_vec);
		//inline Vector4 operator*(const Vector4& i_vec, const Matrix4& i_mtx);


			



			
		};

		
}

#include "Vector4.inl"