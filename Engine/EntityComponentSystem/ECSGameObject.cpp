#include "ECSGameObject.h"
#include "ECSGameObject.h"

#include <Engine/EntityComponentSystem/PhysicsSystem.h>
#include <Engine/EntityComponentSystem/RenderComponent.h>

eae6320::ECS::ECSGameObject::ECSGameObject()
{
	m_rigidBody = SmartPointer<eae6320::Physics::sRigidBodyState>(new eae6320::Physics::sRigidBodyState());
	m_pointer = SmartPointer<ECS::ECSEntity>(new ECS::ECSEntity(*this));
}

eae6320::ECS::ECSGameObject::ECSGameObject(eae6320::Graphics::Geometry* i_geometry, eae6320::Graphics::Effect* i_effect)
{
	m_rigidBody = SmartPointer<eae6320::Physics::sRigidBodyState>(new eae6320::Physics::sRigidBodyState());
	m_pointer = SmartPointer<ECS::ECSEntity>(new ECS::ECSEntity(*this));
}

eae6320::ECS::ECSGameObject::~ECSGameObject()
{
	
}

eae6320::cResult eae6320::ECS::ECSGameObject::Init(eae6320::Graphics::Geometry* i_geometry, eae6320::Graphics::Effect* i_effect, float i_drag, float i_maxSpeed)
{
	cResult result = Results::Success;

	m_rigidBody.operator*().drag = i_drag;
	m_rigidBody.operator*().maxSpeed = i_maxSpeed;

	eae6320::ECS::PhysicsSystem::CreatePhysicsComponent(m_rigidBody, m_pointer);
	eae6320::ECS::RenderComponent::CreateRenderComponent(i_geometry, i_effect, m_rigidBody, m_pointer);
	return result;
}

eae6320::cResult eae6320::ECS::ECSGameObject::CleanUp()
{
	cResult result = Results::Success;
	eae6320::ECS::PhysicsSystem::RemovePhysicsComponent(m_pointer);
	eae6320::ECS::RenderComponent::RemoveRenderComponent(m_pointer);
	return result;
}
