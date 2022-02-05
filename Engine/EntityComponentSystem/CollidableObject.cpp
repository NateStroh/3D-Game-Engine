#include "CollidableObject.h"

#include <Engine/EntityComponentSystem/RenderComponent.h>
#include <Engine/Logging/Logging.h>

void eae6320::ECS::CollidableObject::ResolveCollision(eae6320::Collision::sCollision coll)
 {
 	if (coll.colliderA->CollisionType == 0 && (coll.colliderB->CollisionType == 1 || coll.colliderB->CollisionType == 2)) {
		eae6320::Logging::OutputMessage("character should die");
	}
	
 	if ((coll.colliderA->CollisionType == 1 && coll.colliderB->CollisionType == 2) || (coll.colliderA->CollisionType == 2 && coll.colliderB->CollisionType == 1)) {
		coll.colliderA->rigidbody->position = { 0,500,0 };
		coll.colliderA->rigidbody->velocity = {0,0,0};
		coll.colliderB->rigidbody->position = { 0,500,0 };
		coll.colliderB->rigidbody->velocity = { 0,0,0 };
	}
}

eae6320::ECS::CollidableObject::CollidableObject()
{
	m_rigidBody = SmartPointer<eae6320::Physics::sRigidBodyState>(new eae6320::Physics::sRigidBodyState());
	m_pointer = SmartPointer<ECS::ECSEntity>(new ECS::ECSEntity(*this));
}

eae6320::ECS::CollidableObject::CollidableObject(eae6320::Graphics::Geometry* i_geometry, eae6320::Graphics::Effect* i_effect)
{
	m_rigidBody = SmartPointer<eae6320::Physics::sRigidBodyState>(new eae6320::Physics::sRigidBodyState());
	m_pointer = SmartPointer<ECS::ECSEntity>(new ECS::ECSEntity(*this));
}

eae6320::ECS::CollidableObject::~CollidableObject()
{

}

eae6320::cResult eae6320::ECS::CollidableObject::Init(eae6320::Graphics::Geometry* i_geometry, eae6320::Graphics::Effect* i_effect, Math::sVector i_extents, bool isTrigger, uint16_t i_collisionType, float i_drag, float i_maxSpeed)
{
	cResult result = Results::Success;

	m_rigidBody.operator*().drag = i_drag;
	m_rigidBody.operator*().maxSpeed = i_maxSpeed;

	eae6320::Collision::cCollider::CreateCollider(i_collisionType, &m_rigidBody.operator*(), i_extents, isTrigger, m_collider);
	//m_collider->ListenToCollision(std::bind(&eae6320::ECS::CollidableObject::ResolveCollision, this, std::placeholders::_1));m_collider->ListenToCollision(std::bind(&eae6320::ECS::CollidableObject::ResolveCollision, this, std::placeholders::_1));
	//m_collider->ListenToCollision(std::bind(&eae6320::cMyGame:, this, std::placeholders::_1));

	eae6320::ECS::RenderComponent::CreateRenderComponent(i_geometry, i_effect, m_rigidBody, m_pointer);
	return result;
}

eae6320::cResult eae6320::ECS::CollidableObject::CleanUp()
{
	cResult result = Results::Success;
	eae6320::ECS::RenderComponent::RemoveRenderComponent(m_pointer);
	return result;
}