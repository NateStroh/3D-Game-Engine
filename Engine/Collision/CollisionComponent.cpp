#include "CollisionComponent.h"

eae6320::CollisionComponent::CollisionComponent()
{
	ColliderObject = eae6320::Collision::Collider();

}

void eae6320::CollisionComponent::UpdateLocation(eae6320::Math::Vector3 Loc)
{
	LastLoc = Loc;
	ColliderObject.Location = Loc;
}

void eae6320::CollisionComponent::SetActive(bool bSetToActive)
{
	if (bSetToActive)
	{
		eae6320::Collision::AddCollisionComponent(this);
	}
}

void eae6320::CollisionComponent::SetParameters(eae6320::Math::Vector3 Extents)
{
	ColliderObject.Box.Extents = Extents;
}

void eae6320::CollisionComponent::AddCollisionBinding(std::function<void(eae6320::Collision::Collider)> function)
{
	Callback = std::bind(function,std::placeholders::_1);

}

void eae6320::CollisionComponent::BroadcastCallback(eae6320::Collision::Collider CollidedObject)
{
	
	Callback(CollidedObject);
	
}
