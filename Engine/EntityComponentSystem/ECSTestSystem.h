#ifndef EAE6320_ECSTESTSYSTEM_H
#define EAE6320_ECSTESTSYSTEM_H

#include <Engine/EntityComponentSystem/ComponentSystem.h>
#include <Engine/Results/Results.h>

#include <string>

namespace eae6320
{
	namespace ECS {
		struct TestComponent {
			std::string m_test;

			TestComponent() : 
				m_test("Default")
			{ }

			TestComponent(const TestComponent &other) : 
				m_test(other.m_test)
			{ }
		};

		class ECSTestSystem {
		private:
			ComponentSystem<TestComponent> m_testComponentList;
		public:
			cResult Init();

			cResult Update(const float i_elapsedSecondCount_systemTime, const float i_elapsedSecondCount_sinceLastSimulationUpdate);

			cResult Print(TestComponent i_component, const float i_elapsedSecondCount_systemTime, const float i_elapsedSecondCount_sinceLastSimulationUpdate);

			cResult CreateTestComponent(std::string i_stringInput, SmartPointer<ECSEntity> i_entity);

			cResult RemoveTestComponent(SmartPointer<ECSEntity> i_entity);

			TestComponent* GetTestComponent(SmartPointer<ECSEntity> i_entity);

			cResult CleanUp();
		};
	}
}

#endif