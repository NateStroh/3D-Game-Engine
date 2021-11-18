#include "ECSTestSystem.h"

#include <Engine/Logging/Logging.h>

eae6320::cResult eae6320::ECS::ECSTestSystem::Print(TestComponent i_component, const float i_elapsedSecondCount_systemTime, const float i_elapsedSecondCount_sinceLastSimulationUpdate) {
	cResult result = Results::Success;
	Logging::OutputMessage(i_component.m_test.c_str());
	return result;
}

eae6320::cResult eae6320::ECS::ECSTestSystem::CreateTestComponent(std::string i_stringInput, SmartPointer<ECSEntity> i_entity)
{
	cResult result = Results::Success;
	TestComponent component;
	component.m_test = i_stringInput;
	m_testComponentList.AddComponentToList(component, i_entity);
	return result;
}

eae6320::cResult eae6320::ECS::ECSTestSystem::RemoveTestComponent(SmartPointer<ECSEntity> i_entity)
{
	return m_testComponentList.RemoveComponentFromList(i_entity);
}

eae6320::ECS::TestComponent* eae6320::ECS::ECSTestSystem::GetTestComponent(SmartPointer<ECSEntity> i_entity)
{
	return m_testComponentList.GetComponent(i_entity);
}

eae6320::cResult eae6320::ECS::ECSTestSystem::Init()
{
	return eae6320::cResult();
}

eae6320::cResult eae6320::ECS::ECSTestSystem::Update(const float i_elapsedSecondCount_systemTime, const float i_elapsedSecondCount_sinceLastSimulationUpdate)
{
	cResult result = Results::Success;
	for (unsigned int i = 0; i < m_testComponentList.Size(); i++) {
		if ((*m_testComponentList.m_componentArray[i]).m_entity.CreateSmartPointer())
			Print((*m_testComponentList.m_componentArray[i]).m_componentData, i_elapsedSecondCount_systemTime, i_elapsedSecondCount_sinceLastSimulationUpdate);
	}

	return result;
}

eae6320::cResult eae6320::ECS::ECSTestSystem::CleanUp()
{
	return eae6320::cResult();
}
