#include "Matrix4.h"
#include "DataTypeMath.h"
#include <cmath>

 namespace eae6320
{
	 namespace Math
	{
		


	Matrix4::Matrix4()
	{
		//m_elements = std::array<float, 16>();
		m_elements[0].fill(0); //make em all zerop
		m_elements[1].fill(0);
		m_elements[2].fill(0);
		m_elements[3].fill(0);
		
	    this->m_elements[0][0] = 1;
	    this->m_elements[1][1] = 1;
	    this->m_elements[2][2] = 1;
	    this->m_elements[3][3] = 1;
	}

	Matrix4::Matrix4(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k,
		float l, float m, float n, float o, float p)
	{
		m_elements[0][0] = a;
		m_elements[0][1] = b;
		m_elements[0][2] = c;
		m_elements[0][3] = d;
		m_elements[1][0] = e;
		m_elements[1][1] = f;
		m_elements[1][2] = g;
		m_elements[1][3] = h;
		m_elements[2][0] = i;
		m_elements[2][1] = j;
		m_elements[2][2] = k;
		m_elements[2][3] = l;
		m_elements[3][0] = m;
		m_elements[3][1] = m;
		m_elements[3][2] = o;
		m_elements[3][3] = p;
		
	}


	Matrix4 Matrix4::CreateScale(float x, float y, float z)
	{
	    Matrix4 newMatrix = Matrix4();
	    newMatrix.m_elements[0][0] = x;
	    newMatrix.m_elements[1][1] = y;
	    newMatrix.m_elements[2][2] = z;
		newMatrix.m_elements[3][3] = 1;
	    return newMatrix;
	}

	Matrix4 Matrix4::CreateTranslation(float x, float y, float z)
	{
	    Matrix4 newMatrix = Matrix4();
	    newMatrix.m_elements[3][0] = x;
	    newMatrix.m_elements[3][1] = y;
	    newMatrix.m_elements[3][2] = z;
	    return newMatrix;
	}

	Matrix4 Matrix4::CreateTranslation(const Vector4 m_Vec)
	{
		Matrix4 newMatrix = Matrix4();
		newMatrix.m_elements[3][0] = m_Vec.x();
		newMatrix.m_elements[3][1] = m_Vec.y();
		newMatrix.m_elements[3][2] = m_Vec.z();
		return newMatrix;
	}
	
	 	
	Matrix4 Matrix4::CreateRotationX(float angle)
	{
	    Matrix4 newMatrix = Matrix4();
	    newMatrix.m_elements[1][1] = std::cos(DegreesToRadians(-angle));
	    newMatrix.m_elements[2][1] = -std::sin(DegreesToRadians(-angle));
	    newMatrix.m_elements[0][2] = std::sin(DegreesToRadians(-angle));
	    newMatrix.m_elements[2][2] = std::cos(DegreesToRadians(-angle));
	    return newMatrix;
	}

	Matrix4 Matrix4::CreateRotationY(float angle)
	{
	    Matrix4 newMatrix = Matrix4();
	    newMatrix.m_elements[0][0] = std::cos(DegreesToRadians(-angle));
	    newMatrix.m_elements[2][0] = std::sin(DegreesToRadians(-angle));
	    newMatrix.m_elements[0][2] = -std::sin(DegreesToRadians(-angle));
	    newMatrix.m_elements[2][2] = std::cos(DegreesToRadians(-angle));
	    return newMatrix;
	}

	Matrix4 Matrix4::CreateRotationZ(float angle)
	{
	    Matrix4 newMatrix = Matrix4();
	    newMatrix.m_elements[0][0] = std::cos(DegreesToRadians(-angle));
	    newMatrix.m_elements[1][0] = -std::sin(DegreesToRadians(-angle));
	    newMatrix.m_elements[0][1] = std::sin(DegreesToRadians(-angle));
	    newMatrix.m_elements[1][1] = std::cos(DegreesToRadians(-angle));
	    return newMatrix;
	}

	Matrix4 Matrix4::GetTranspose()
	{
		Matrix4 NewMatrix = Matrix4();


		NewMatrix.SetColumn(GetRow(0), 0);
		NewMatrix.SetColumn(GetRow(1), 1);
		NewMatrix.SetColumn(GetRow(2), 2);
		NewMatrix.SetColumn(GetRow(3), 3);

		return NewMatrix;
	}

	 



	 Vector4 Matrix4::GetColumn(int colNum) const
	{
		return Vector4(m_elements[colNum][0], m_elements[colNum][1], m_elements[colNum][2], m_elements[colNum][3]);
		
	}
	 Vector4 Matrix4::GetRow(int rowNum) const
	{
		return Vector4(m_elements[0][rowNum], m_elements[1][rowNum], m_elements[2][rowNum], m_elements[3][rowNum]);
	}

	 void Matrix4::SetRow(Vector4 NewRow, int rowNum)
	 {
		 m_elements[0][rowNum] = NewRow.x();
		 m_elements[1][rowNum] = NewRow.y();
		 m_elements[2][rowNum] = NewRow.z();
		 m_elements[3][rowNum] = NewRow.w();
	 }
	 void Matrix4::SetColumn(Vector4 NewCol, int colNum)
	 {
		 m_elements[colNum][0] = NewCol.x();
		 m_elements[colNum][1] = NewCol.y();
		 m_elements[colNum][2] = NewCol.z();
		 m_elements[colNum][3] = NewCol.w();
	 }






	 	

	 float Matrix4::GetDeterminant()
	 {
		 return
			 m_elements[0][ 3] * m_elements[1][ 2] * m_elements[2][ 1] * m_elements[3][ 0] - m_elements[0][ 2] * m_elements[1][ 3] * m_elements[2][ 1] * m_elements[3][ 0] -
			 m_elements[0][ 3] * m_elements[1][ 1] * m_elements[2][ 2] * m_elements[3][ 0] + m_elements[0][ 1] * m_elements[1][ 3] * m_elements[2][ 2] * m_elements[3][ 0] +
			 m_elements[0][ 2] * m_elements[1][ 1] * m_elements[2][ 3] * m_elements[3][ 0] - m_elements[0][ 1] * m_elements[1][ 2] * m_elements[2][ 3] * m_elements[3][ 0] -
			 m_elements[0][ 3] * m_elements[1][ 2] * m_elements[2][ 0] * m_elements[3][ 1] + m_elements[0][ 2] * m_elements[1][ 3] * m_elements[2][ 0] * m_elements[3][ 1] +
			 m_elements[0][ 3] * m_elements[1][ 0] * m_elements[2][ 2] * m_elements[3][ 1] - m_elements[0][ 0] * m_elements[1][ 3] * m_elements[2][ 2] * m_elements[3][ 1] -
			 m_elements[0][ 2] * m_elements[1][ 0] * m_elements[2][ 3] * m_elements[3][ 1] + m_elements[0][ 0] * m_elements[1][ 2] * m_elements[2][ 3] * m_elements[3][ 1] +
			 m_elements[0][ 3] * m_elements[1][ 1] * m_elements[2][ 0] * m_elements[3][ 2] - m_elements[0][ 1] * m_elements[1][ 3] * m_elements[2][ 0] * m_elements[3][ 2] -
			 m_elements[0][ 3] * m_elements[1][0] * m_elements[2][ 1] * m_elements[3][ 2] + m_elements[0][ 0] * m_elements[1][ 3] * m_elements[2][ 1] * m_elements[3][ 2] +
			 m_elements[0][ 1] * m_elements[1][ 0] * m_elements[2][ 3] * m_elements[3][ 2] - m_elements[0][ 0] * m_elements[1][ 1] * m_elements[2][ 3] * m_elements[3][ 2] -
			 m_elements[0][ 2] * m_elements[1][ 1] * m_elements[2][ 0] * m_elements[3][ 3] + m_elements[0][ 1] * m_elements[1][ 2] * m_elements[2][ 0] * m_elements[3][ 3] +
			 m_elements[0][ 2] * m_elements[1][ 0] * m_elements[2][ 1] * m_elements[3][ 3] - m_elements[0][ 0] * m_elements[1][ 2] * m_elements[2][ 1] * m_elements[3][ 3] -
			 m_elements[0][ 1] * m_elements[1][ 0] * m_elements[2][ 2] * m_elements[3][ 3] + m_elements[0][ 0] * m_elements[1][ 1] * m_elements[2][ 2] * m_elements[3][ 3];
	 }


	 	
	Matrix4 Matrix4::GetInverse()
	{
		
		Matrix4 Inverse = Matrix4();


		Vector4 col = GetColumn(3);
		Matrix4 OnlyRot = *this;
		OnlyRot.SetColumn(Vector3(0,0,0),3);
		Matrix4 RotTranspose = OnlyRot.GetTranspose();
		
		col = (-1 * RotTranspose) * col;
		col.w(1);


		Inverse = RotTranspose;
		Inverse.SetColumn(col, 3);

		return Inverse;
		

	}
	 }
}