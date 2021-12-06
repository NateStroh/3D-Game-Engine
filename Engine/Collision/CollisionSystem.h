#pragma once

#include <Engine/Math/sVector.h>
#include "CollisionTypes.h"
#include	"Vector3.h"


namespace eae6320
{
	class CollisionComponent;

	namespace Collision
	{


		bool AreColliding(Collider A, Collider B);
		bool IsColliding(Collider A, Collider B, float i_dt, float& CollTime, eae6320::Math::Vector3& InCollisionAxisNormal);

		void ResolveCollision(const CollisionPair Collision);
		void ResolveCollisions(float i_dt);

		void AddCollisionComponent(eae6320::CollisionComponent* i_Comp);

		void RunAllCollisionTests();

		void AddCollider(Collider InCollider);
		
		

	}


}
