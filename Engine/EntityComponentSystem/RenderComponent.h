#ifndef EAE6320_RENDERCOMPONENT_H
#define EAE6320_RENDERCOMPONENT_H

#include <Engine/Graphics/Effect.h>
#include <Engine/Graphics/Geometry.h>
#include <Engine/EntityComponentSystem/ComponentSystem.h>

namespace eae6320
{
	namespace ECS
	{
		struct SRenderComponent {
			eae6320::Graphics::Geometry* m_geometry;
			eae6320::Graphics::Effect* m_effect;
			WeakPointer<eae6320::Physics::sRigidBodyState> m_rigidBody;

			SRenderComponent() :
				m_geometry(nullptr),
				m_effect(nullptr),
				m_rigidBody(nullptr)
			{ }

			SRenderComponent(const SRenderComponent& other) :
				m_geometry(other.m_geometry),
				m_effect(other.m_effect),
				m_rigidBody(other.m_rigidBody)
			{ }

			SRenderComponent(eae6320::Graphics::Geometry* i_geometry, eae6320::Graphics::Effect* i_effect, SmartPointer<eae6320::Physics::sRigidBodyState> i_rigidBody) :
				m_geometry(i_geometry),
				m_effect(i_effect),
				m_rigidBody(i_rigidBody)
			{ }
		};

		namespace  RenderComponent {
			extern ComponentSystem<SRenderComponent> m_renderComponentList;

			cResult Init();

			cResult Update(const float i_elapsedSecondCount_systemTime, const float i_elapsedSecondCount_sinceLastSimulationUpdate);

			cResult Render(SRenderComponent i_component, const float i_elapsedSecondCount_systemTime, const float i_elapsedSecondCount_sinceLastSimulationUpdate);

			cResult CreateRenderComponent(eae6320::Graphics::Geometry* i_geometry, eae6320::Graphics::Effect* i_effect, SmartPointer<eae6320::Physics::sRigidBodyState> i_rigidBody, SmartPointer<ECSEntity> i_entity);

			cResult RemoveRenderComponent(SmartPointer<ECSEntity> i_entity);

			SRenderComponent* GetRenderComponent(SmartPointer<ECSEntity> i_entity);

			cResult CleanUp();
		};
	}
}

#endif