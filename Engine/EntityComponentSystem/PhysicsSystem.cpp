#include "PhysicsSystem.h"

eae6320::ECS::ComponentSystem<eae6320::ECS::SPhysicsComponent> eae6320::ECS::PhysicsSystem::m_PhysicsSystemComponentList = *new eae6320::ECS::ComponentSystem<eae6320::ECS::SPhysicsComponent>();

eae6320::cResult eae6320::ECS::PhysicsSystem::Tick(SPhysicsComponent i_component, const float i_elapsedSecondCount_sinceLastSimulationUpdate)
{
	cResult result = Results::Success;
	SmartPointer<eae6320::Physics::sRigidBodyState> rigidBody =  i_component.m_rigidBody.CreateSmartPointer();
	(*rigidBody).Update(i_elapsedSecondCount_sinceLastSimulationUpdate);
	return result;
}

eae6320::cResult eae6320::ECS::PhysicsSystem::Init()
{
	cResult result = Results::Success;

	return result;
}

eae6320::cResult eae6320::ECS::PhysicsSystem::Update(const float i_sinceLastSimulationUpdate)
{
	cResult result = Results::Success;

	for (SmartPointer<ECS::ComponentData<SPhysicsComponent>> component : m_PhysicsSystemComponentList.m_componentList) {
		if ((*component).m_entity.CreateSmartPointer())
			Tick((*component).m_componentData, i_sinceLastSimulationUpdate);
	}

	return result;
}

eae6320::cResult eae6320::ECS::PhysicsSystem::CreatePhysicsComponent(SmartPointer<eae6320::Physics::sRigidBodyState> i_rigidBody, SmartPointer<ECSEntity> i_entity)
{
	cResult result = Results::Success;
	SPhysicsComponent physicsComponent(i_rigidBody);
	m_PhysicsSystemComponentList.AddComponentToList(physicsComponent, i_entity);
	return result;
}

eae6320::cResult eae6320::ECS::PhysicsSystem::RemovePhysicsComponent(SmartPointer<ECSEntity> i_entity)
{
	cResult result = Results::Success;
	m_PhysicsSystemComponentList.RemoveComponentFromList(i_entity);
	return result;
}

eae6320::ECS::SPhysicsComponent* eae6320::ECS::PhysicsSystem::GetPhysicsComponent(SmartPointer<ECSEntity> i_entity)
{
	return m_PhysicsSystemComponentList.GetComponent(i_entity);
}

eae6320::cResult eae6320::ECS::PhysicsSystem::CleanUp()
{
	cResult result = Results::Success;
	m_PhysicsSystemComponentList.m_componentList.clear();
	return result;
}
