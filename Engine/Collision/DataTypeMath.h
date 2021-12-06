#pragma once
#define _USE_MATH_DEFINES
#include "Matrix4.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Vector2.h"
#include <cmath>
#include <math.h>

namespace eae6320
{
	namespace Math
	{

		inline float DegreesToRadians(float degrees)
		{
			//return degrees * (float)M_PI / 180;
			return degrees * 3.1415f / 180;
		}



		
		////////////Vec 4

		inline Vector4 operator*(const Matrix4& i_mtx, const Vector4& i_vec)
		{
			Vector4 NewVec;



			NewVec.x(dot(i_vec, i_mtx.GetRow(0)));
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
		////////////////End of Vec 4////////////////


		//////////////////VECTOR 3./////////////////

		inline Vector3 operator*(const Matrix4& i_mtx, const Vector3& i_vec)
		{
			Vector3 NewVec;
			Vector4 GrowVec = Vector4(i_vec);



			NewVec.x(dot(GrowVec, i_mtx.GetRow(0)));
			NewVec.y(dot(GrowVec, i_mtx.GetRow(1)));
			NewVec.z(dot(GrowVec, i_mtx.GetRow(2)));
			//NewVec.w(dot(GrowVec, i_mtx.GetRow(3)));
			return NewVec;
		}
		inline Vector3 operator*(const Vector3& i_vec, const Matrix4& i_mtx)
		{
			Vector3 NewVec;
			Vector4 GrowVec = Vector4(i_vec);


			NewVec.x(dot(GrowVec, i_mtx.GetRow(0)));
			NewVec.y(dot(GrowVec, i_mtx.GetRow(1)));
			NewVec.z(dot(GrowVec, i_mtx.GetRow(2)));
			//NewVec.w(dot(GrowVec, i_mtx.GetRow(3)));
			return NewVec;
		}


		/////////////////////END OF VEC 3////////////////
		
	}
}