#ifndef EAE6320_ECSTESTSYSTEM_H
#define EAE6320_ECSTESTSYSTEM_H

#include <Engine/EntityComponentSystem/ComponentSystem.h>
#include <Engine/Results/Results.h>

#include <string>

namespace eae6320
{
	namespace ECS {
		struct TestComponent {
			unsigned int id;
			std::string m_test;
		};

		class ECSTestSystem {
		private:
			ComponentSystem<TestComponent> m_testComponent;
		public:
			cResult Init();

			cResult Update(const float i_elapsedSecondCount_systemTime, const float i_elapsedSecondCount_sinceLastSimulationUpdate);

			cResult Print(TestComponent i_component, const float i_elapsedSecondCount_systemTime, const float i_elapsedSecondCount_sinceLastSimulationUpdate);

			cResult CreateTestComponent(std::string i_stringInput, unsigned int i_ID);

			cResult CleanUp();
		};
	}
}

#endif