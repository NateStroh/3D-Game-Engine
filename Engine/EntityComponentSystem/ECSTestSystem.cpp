#include "ECSTestSystem.h"

#include <Engine/Logging/Logging.h>

eae6320::cResult eae6320::ECS::ECSTestSystem::Print(TestComponent i_component, const float i_elapsedSecondCount_systemTime, const float i_elapsedSecondCount_sinceLastSimulationUpdate) {
	Logging::OutputMessage(i_component.m_test.c_str());
	return eae6320::cResult();
}

eae6320::cResult eae6320::ECS::ECSTestSystem::CreateTestComponent(std::string i_stringInput, SmartPointer<ECSEntity> i_entity)
{
	TestComponent component;
	component.m_test = i_stringInput;
	m_testComponent.AddComponentToList(component, i_entity);
	return cResult();
}

eae6320::cResult eae6320::ECS::ECSTestSystem::RemoveTestComponent(SmartPointer<ECSEntity> i_entity)
{
	return m_testComponent.RemoveComponentFromList(i_entity);
}

eae6320::ECS::TestComponent* eae6320::ECS::ECSTestSystem::GetTestComponent(SmartPointer<ECSEntity> i_entity)
{
	return m_testComponent.GetComponent(i_entity);
}

eae6320::cResult eae6320::ECS::ECSTestSystem::Init()
{
	return eae6320::cResult();
}

eae6320::cResult eae6320::ECS::ECSTestSystem::Update(const float i_elapsedSecondCount_systemTime, const float i_elapsedSecondCount_sinceLastSimulationUpdate)
{
	//for (SmartPointer<ECS::ComponentData<TestComponent>> component : m_testComponent.m_componentList) {
	//	if((*component).m_entity.CreateSmartPointer())
	//		Print((*component).m_componentData, i_elapsedSecondCount_systemTime, i_elapsedSecondCount_sinceLastSimulationUpdate);
	//}

	for (unsigned int i = 0; i < m_testComponent.Size(); i++) {
		if ((*m_testComponent.m_componentArray[i]).m_entity.CreateSmartPointer())
			Print((*m_testComponent.m_componentArray[i]).m_componentData, i_elapsedSecondCount_systemTime, i_elapsedSecondCount_sinceLastSimulationUpdate);
	}

	return cResult();
}

eae6320::cResult eae6320::ECS::ECSTestSystem::CleanUp()
{
	return eae6320::cResult();
}
