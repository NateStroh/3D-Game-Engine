#include "ECSGameObject.h"
#include "ECSGameObject.h"

#include <Engine/EntityComponentSystem/PhysicsSystem.h>
#include <Engine/EntityComponentSystem/RenderComponent.h>

eae6320::ECS::ECSGameObject::ECSGameObject()
{
	m_rigidBody = SmartPointer<eae6320::Physics::sRigidBodyState>(new eae6320::Physics::sRigidBodyState());
}

eae6320::ECS::ECSGameObject::~ECSGameObject()
{

}
