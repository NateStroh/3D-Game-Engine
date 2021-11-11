#include "ECSTestSystem.h"

#include <Engine/Logging/Logging.h>

eae6320::cResult eae6320::ECS::ECSTestSystem::Print(TestComponent i_component, const float i_elapsedSecondCount_systemTime, const float i_elapsedSecondCount_sinceLastSimulationUpdate) {
	Logging::OutputMessage(i_component.m_test.c_str());
	return eae6320::cResult();
}

eae6320::cResult eae6320::ECS::ECSTestSystem::CreateTestComponent(std::string i_stringInput, unsigned int i_ID)
{
	TestComponent component;
	component.id = i_ID;
	component.m_test = i_stringInput;
	m_testComponent.AddComponentToList(component);
	return cResult();
}

eae6320::cResult eae6320::ECS::ECSTestSystem::Init()
{
	return eae6320::cResult();
}

eae6320::cResult eae6320::ECS::ECSTestSystem::Update(const float i_elapsedSecondCount_systemTime, const float i_elapsedSecondCount_sinceLastSimulationUpdate)
{
	for (TestComponent component : m_testComponent.m_componentList) {
		Print(component, i_elapsedSecondCount_systemTime, i_elapsedSecondCount_sinceLastSimulationUpdate);
	}
	return cResult();
}

eae6320::cResult eae6320::ECS::ECSTestSystem::CleanUp()
{
	return eae6320::cResult();
}
