namespace eae6320
{
	namespace Math
	{

        

		inline Matrix4& Matrix4::operator+=(const Matrix4& i_i_other)
		{
			for (auto i = 0; i < 4; ++i)
			{
				for (auto j = 0; j<4; ++j)
				{
					m_elements[i][j] += i_i_other.m_elements[i][j];
				}
				
			}
			return *this;
		}
		inline Matrix4& Matrix4::operator-=(const Matrix4& i_i_other)
		{
			for (auto i = 0; i < 4; ++i)
			{
				for (auto j = 0; j < 4; ++j)
				{
					m_elements[i][j] -= i_i_other.m_elements[i][j];
				}

			}
			return *this;
		}

		inline Matrix4& Matrix4::operator*=(const Matrix4& i_other)
		{

			Matrix4 newMatrix = Matrix4();
			float num = 0;

			for(int i = 0; i < 4; ++i)
			{
				for(int j = 0 ; j < 4; ++j)
				{
					num = 0;
					for(int k = 0; k < 4; ++k)
					{
						num += m_elements[i][j] * i_other.m_elements[k][j];
					}
					newMatrix.m_elements[i][j] = num;
					
				}
			}
			
			return newMatrix;
			
		}
		inline Matrix4& Matrix4::operator*=(float i_val)
		{
			for (auto i = 0; i < 4; ++i)
			{
				for (auto j = 0; j < 4; ++j)
				{
					m_elements[i][j] *= i_val;
				}

			}
			return *this;
		}

		inline Matrix4& Matrix4::operator/=(const Matrix4& i_other)
		{

			Matrix4 newMatrix = Matrix4();
			float num = 0;

			for (int i = 0; i < 4; ++i)
			{
				for (int j = 0; j < 4; ++j)
				{
					num = 0;
					for (int k = 0; k < 4; ++k)
					{
						num += m_elements[i][j] / i_other.m_elements[k][j];
					}
					newMatrix.m_elements[i][j] = num;

				}
			}

			return newMatrix;
		}
		inline Matrix4& Matrix4::operator/=(float i_val)
		{
			for (auto i = 0; i < 4; ++i)
			{
				for (auto j = 0; j < 4; ++j)
				{
					m_elements[i][j] /= i_val;
				}

			}
			return *this;
		}
		
		inline Matrix4 operator*(const Matrix4& i_lhs, float i_rhs)
		{
			Matrix4 NewMatrix = i_lhs;
			for (int i = 0; i < 4; ++i)
			{
				for (int j = 0; j < 4; ++j)
				{
					NewMatrix.m_elements[i][j] *= i_rhs;
				}
			}
			return NewMatrix;
		}
		inline Matrix4 operator*(float i_lhs, const Matrix4& i_rhs)
		{
			Matrix4 NewMatrix = i_rhs;
			for(int i = 0; i < 4; ++i)
			{
				for(int j = 0; j < 4; ++j)
				{
					NewMatrix.m_elements[i][j] *= i_lhs;
				}
			}
			return NewMatrix;
		}

		inline Matrix4 operator*(const Matrix4& i_lhs, const Matrix4& rhs)
		{
			Matrix4 newMatrix = Matrix4();


			float num = 0;

			for (int i = 0; i < 4; ++i)
			{
				for (int j = 0; j < 4; ++j)
				{
					num = 0;
					for (int k = 0; k < 4; ++k)
					{
						num += i_lhs.m_elements[i][k] * rhs.m_elements[k][j];
					}
					newMatrix.m_elements[i][j] = num;

				}
			}


			return  newMatrix;
		}

		inline Matrix4::Matrix4(const Matrix4& i_other)
		{
			m_elements = i_other.m_elements;
		}
		// assignment operator
		inline Matrix4& Matrix4::operator=(const Matrix4& i_rhs)
		{
			m_elements = i_rhs.m_elements;


			return *this;
		}


		inline bool operator==(const Matrix4& i_lhs, const Matrix4& i_rhs)
		{
			for (int i = 0; i < 4; ++i)
			{
				for (int j = 0; j < 4; ++j)
				{
					if(i_lhs.m_elements[i][j] != i_rhs.m_elements[i][j])
					{
						return false;
					}
				}
			}
			return true;
		}
		inline bool operator!=(const Matrix4& i_lhs, const Matrix4& i_rhs)
		{
			for (int i = 0; i < 4; ++i)
			{
				for (int j = 0; j < 4; ++j)
				{
					if (i_lhs.m_elements[i][j] == i_rhs.m_elements[i][j])
					{
						return false;
					}
				}
			}
			return true;
		}


		inline Matrix4 operator+(const Matrix4& i_lhs, const Matrix4& i_rhs)
		{
			Matrix4 newMatrix = Matrix4();


			float num = 0;

			for (int i = 0; i < 4; ++i)
			{
				for (int j = 0; j < 4; ++j)
				{
					
					newMatrix.m_elements[i][j] = i_lhs.m_elements[i][j] + i_rhs.m_elements[i][j];

				}
			}


			return  newMatrix;
		}
		inline Matrix4 operator-(const Matrix4& i_lhs, const Matrix4& i_rhs)
		{
			Matrix4 newMatrix = Matrix4();


			float num = 0;

			for (int i = 0; i < 4; ++i)
			{
				for (int j = 0; j < 4; ++j)
				{

					newMatrix.m_elements[i][j] = i_lhs.m_elements[i][j] - i_rhs.m_elements[i][j];

				}
			}


			return  newMatrix;
		}
		inline Matrix4 operator/(const Matrix4& i_lhs, const Matrix4& i_rhs)
		{
			Matrix4 newMatrix = Matrix4();


			float num = 0;

			for (int i = 0; i < 4; ++i)
			{
				for (int j = 0; j < 4; ++j)
				{

					newMatrix.m_elements[i][j] = i_lhs.m_elements[i][j] / i_rhs.m_elements[i][j];

				}
			}


			return  newMatrix;
		}
		inline Matrix4 operator/(const Matrix4& i_lhs, float i_rhs)
		{
			Matrix4 newMatrix = Matrix4();


			float num = 0;

			for (int i = 0; i < 4; ++i)
			{
				for (int j = 0; j < 4; ++j)
				{

					newMatrix.m_elements[i][j] = i_lhs.m_elements[i][j] / i_rhs;

				}
			}


			return  newMatrix;
		}
		
	}
}