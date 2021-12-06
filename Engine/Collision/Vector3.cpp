#include "Vector3.h"




namespace eae6320
{
	namespace Math
	{

		const Vector3 Vector3::Zero(0.0f, 0.0f, 0.0f);

		Vector3 Vector3::Normalized() const
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

		Vector3 Normalized(const Vector3& i_vec)
		{
			float length = i_vec.Length();

			if (length == 0.0f)
				return Vector3::Zero;
			else
			{
				float inv_length = 1.0f / length;

				return i_vec * inv_length;
			}
		}

	} // namespace Math
} // namespace Engine
