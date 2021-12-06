#include "Vector4.h"
//#include "DataTypes/Vector4.h"




namespace eae6320
{
	namespace Math
	{

		const Vector4 Vector4::Zero(0.0f, 0.0f, 0.0f, 0.0f);

		Vector4 Vector4::Normalized() const
		{
			float length = Length();

			if (length == 0.0f)
				return Zero;
			else
			{
				float inv_length = 1.0f / length;

				return *this * inv_length;
			}
		}

		Vector4 Normalized(const Vector4& i_vec)
		{
			float length = i_vec.Length();

			if (length == 0.0f)
				return Vector4::Zero;
			else
			{
				float inv_length = 1.0f / length;

				return i_vec * inv_length;
			}
		}

	} // namespace Math
} // namespace Engine
