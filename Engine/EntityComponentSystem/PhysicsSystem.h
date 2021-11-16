#ifndef EAE6320_PHYSICSSYSTEM_H
#define EAE6320_PHYSICSSYSTEM_H

#include <Engine/EntityComponentSystem/ComponentSystem.h>
#include <Engine/Physics/sRigidBodyState.h>

namespace eae6320
{
	namespace ECS
	{
		struct SPhysicsComponent {
			WeakPointer<eae6320::Physics::sRigidBodyState> m_rigidBody;

			SPhysicsComponent() :
				m_rigidBody(nullptr)
			{ }

			SPhysicsComponent(const SPhysicsComponent& other) :
				m_rigidBody(other.m_rigidBody)
			{ }

			SPhysicsComponent(SmartPointer<eae6320::Physics::sRigidBodyState> i_rigidBody) :
				m_rigidBody(i_rigidBody)
			{ }
		};

		class PhysicsSystem {
			ComponentSystem<SPhysicsComponent> m_PhysicsSystemComponentList;

			cResult Tick(SPhysicsComponent i_component, const float i_elapsedSecondCount_sinceLastSimulationUpdate);
		public:
			cResult Init();

			cResult Update(const float i_sinceLastSimulationUpdate);

			cResult CreatePhysicsComponent(SmartPointer<eae6320::Physics::sRigidBodyState> i_rigidBody, SmartPointer<ECSEntity> i_entity);

			cResult RemovePhysicsComponent(SmartPointer<ECSEntity> i_entity);

			SPhysicsComponent* GetPhysicsComponent(SmartPointer<ECSEntity> i_entity);

			cResult CleanUp();
		};
	}
}

#endif