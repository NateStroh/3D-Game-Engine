#pragma once
#include "Vector4.h"
#include <array>

namespace eae6320
{
	namespace Math
	{
		class Matrix4
		{




		public:

            std::array<std::array<float, 4>,4> m_elements;

			Matrix4();

			Matrix4(float a, float b, float c, float d,
				float e, float f, float g, float h,
				float i, float j, float k, float l,
				float m, float n, float o, float p);
			
            inline Matrix4(const Matrix4& i_other);
            // assignment operator
			inline Matrix4& operator=(const Matrix4& i_rhs);
           


			 Vector4 GetColumn(int colNum) const;
			 void	SetColumn(Vector4 NewCol, int colnum);
			 Vector4 GetRow(int rowNum) const;
			 void	SetRow(Vector4 NewRow, int rownum);
			 float GetDeterminant();
			
			
			static Matrix4 CreateScale(float x, float y, float z);
			static Matrix4 CreateTranslation(float x, float y, float z);
			static Matrix4 CreateTranslation(const Vector4 m_Vec);
			static Matrix4 CreateRotationX(float angle);
			static Matrix4 CreateRotationY(float angle);
			static Matrix4 CreateRotationZ(float angle);


			Matrix4 GetTranspose();
			Matrix4 GetInverse();

			inline Matrix4& operator+=(const Matrix4& i_other);
			inline Matrix4& operator-=(const Matrix4& i_other);

			inline Matrix4& operator*=(const Matrix4& i_other);
			inline Matrix4& operator*=(float i_val);

			inline Matrix4& operator/=(const Matrix4& i_other);
			inline Matrix4& operator/=(float i_val);


			


			
		};

		inline Matrix4 operator*(const Matrix4& i_lhs, const Matrix4& i_rhs);

		inline Matrix4 operator+(const Matrix4& i_lhs, const Matrix4& i_rhs);
		inline Matrix4 operator-(const Matrix4& i_lhs, const Matrix4& i_rhs);

		inline Matrix4 operator*(const Matrix4& i_lhs, float i_rhs);
		inline Matrix4 operator*(float i_lhs, const Matrix4& i_rhs );

		inline Matrix4 operator/(const Matrix4& i_lhs, const Matrix4& i_rhs);
		inline Matrix4 operator/(const Matrix4& i_lhs, float i_rhs);

		inline bool operator==(const Matrix4& i_lhs, const Matrix4& i_rhs);
		inline bool operator!=(const Matrix4& i_lhs, const Matrix4& i_rhs);





		
	}
}
#include "Matrix4.inl"