#pragma once

#include <Engine/Math/sVector.h>

#include	"Vector3.h"



namespace eae6320
{
	namespace Collision
	{


		struct AABB
		{
			eae6320::Math::Vector3 Center;
			eae6320::Math::Vector3 Extents;


		};

		struct Collider
		{
			Collider()
			{
				Box = AABB();
				Box.Extents = eae6320::Math::Vector3(1, 1, 1);
				Box.Center = eae6320::Math::Vector3(0, 0, 0);
			}
			Collider(AABB i_Box, float i_mZRot, eae6320::Math::Vector3 i_location)
				:Box(i_Box), m_ZRot(i_mZRot), Location(i_location)
			{
			}
			AABB Box;
			float m_ZRot = 0;
			eae6320::Math::Vector3 Location;

			void UpdateLocation(eae6320::Math::Vector3 NewLoc)
			{
				Location = NewLoc;
			}

		};
		struct Collision
		{
			Collision(eae6320::Math::Vector3 inNormal, Collider InCollider)
				:
				m_CollisionNormal(inNormal), m_CollisionObject(InCollider)
			{}
			eae6320::Math::Vector3 m_CollisionNormal;
			Collider m_CollisionObject;
		};

		struct CollisionPair
		{
			float m_CollisionTime = 0;
			Collision* A = nullptr;
			Collision* B = nullptr;
		};

	}


}