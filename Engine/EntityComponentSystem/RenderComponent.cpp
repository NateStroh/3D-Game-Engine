#include "RenderComponent.h"

#include <Engine/Graphics/Graphics.h>

eae6320::ECS::ComponentSystem<eae6320::ECS::SRenderComponent> &eae6320::ECS::RenderComponent::m_renderComponentList = *(new eae6320::ECS::ComponentSystem<eae6320::ECS::SRenderComponent>());

eae6320::cResult eae6320::ECS::RenderComponent::Init()
{
	return cResult();
}

eae6320::cResult eae6320::ECS::RenderComponent::Update(const float i_elapsedSecondCount_systemTime, const float i_elapsedSecondCount_sinceLastSimulationUpdate)
{
	cResult result = Results::Success;
	
	for (SmartPointer<ECS::ComponentData<SRenderComponent>> component : m_renderComponentList.m_componentList) {
		if ((*component).m_entity.CreateSmartPointer())
			Render((*component).m_componentData, i_elapsedSecondCount_systemTime, i_elapsedSecondCount_sinceLastSimulationUpdate);
	}
	
	return result;
}

eae6320::cResult eae6320::ECS::RenderComponent::Render(SRenderComponent i_component, const float i_elapsedSecondCount_systemTime, const float i_elapsedSecondCount_sinceLastSimulationUpdate)
{
	cResult result = Results::Success;
	i_component.m_geometry->IncrementReferenceCount();
	i_component.m_effect->IncrementReferenceCount();

	SmartPointer<eae6320::Physics::sRigidBodyState> physicsComponent = i_component.m_rigidBody.CreateSmartPointer();
	auto predictedTransform = (*physicsComponent).PredictFutureTransform(i_elapsedSecondCount_sinceLastSimulationUpdate);
	eae6320::Graphics::AddGeometryEffectPair(i_component.m_geometry, predictedTransform, i_component.m_effect);

	i_component.m_geometry->DecrementReferenceCount();
	i_component.m_effect->DecrementReferenceCount();
	return result;
}

eae6320::cResult eae6320::ECS::RenderComponent::CreateRenderComponent(eae6320::Graphics::Geometry* i_geometry, eae6320::Graphics::Effect* i_effect, SmartPointer<eae6320::Physics::sRigidBodyState> i_rigidBody, SmartPointer<ECSEntity> i_entity)
{
	cResult result = Results::Success;
	SRenderComponent renderComponent(i_geometry, i_effect, i_rigidBody);
	m_renderComponentList.AddComponentToList(renderComponent, i_entity);
	return result;
}

eae6320::cResult eae6320::ECS::RenderComponent::RemoveRenderComponent(SmartPointer<ECSEntity> i_entity)
{
	return m_renderComponentList.RemoveComponentFromList(i_entity);
}

eae6320::cResult eae6320::ECS::RenderComponent::ChangeGeometry(eae6320::Graphics::Geometry* i_geometry, eae6320::Graphics::Effect* i_effect, SmartPointer<ECSEntity> i_entity)
{
	cResult result = Results::Success;

	SRenderComponent* renderComponent = m_renderComponentList.GetComponent(i_entity);
	renderComponent->m_geometry = i_geometry;
	renderComponent->m_effect = i_effect;

	return result;
}

eae6320::ECS::SRenderComponent* eae6320::ECS::RenderComponent::GetRenderComponent(SmartPointer<ECSEntity> i_entity)
{
	return m_renderComponentList.GetComponent(i_entity);
}

eae6320::cResult eae6320::ECS::RenderComponent::CleanUp()
{
	cResult result = Results::Success;
	m_renderComponentList.m_componentList.clear();
	delete &eae6320::ECS::RenderComponent::m_renderComponentList;
	return result;
}
