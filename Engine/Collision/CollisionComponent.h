
#ifndef EAE6320_CollisionComponent_H
#define EAE6320_CollisionComponent_H

#include "CollisionSystem.h"
#include "Vector3.h"
#include <vector>
#include <functional>
namespace eae6320
{


	class CollisionComponent
	{

	public:


		CollisionComponent();

		void UpdateLocation(eae6320::Math::Vector3 Loc);
		void SetActive(bool bSetToActive);

		void SetParameters(eae6320::Math::Vector3 Extents);

		eae6320::Collision::Collider ColliderObject;
		void AddCollisionBinding(std::function<void(eae6320::Collision::Collider)> function);
		std::function<void(eae6320::Collision::Collider)> Callback;
		void BroadcastCallback(eae6320::Collision::Collider CollidedObject);





	private:

	
		
		eae6320::Math::Vector3 LastLoc;
	};



}












#endif