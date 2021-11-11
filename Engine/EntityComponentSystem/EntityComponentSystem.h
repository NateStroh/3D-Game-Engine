#ifndef EAE6320_ENTITYCOMPONENTSYSTEM_H
#define EAE6320_ENTITYCOMPONENTSYSTEM_H

#include <Engine/Results/Results.h>

#include "ComponentSystem.h"

namespace eae6320
{
	namespace ECS {
		class EntityComponentSystem
		{
		private:
			static const unsigned int MAX_COMPONENTS = 500;
			static const unsigned int MAX_SYSTEMS = 500;
			//ComponentSystem m_allComponentSystems[MAX_SYSTEMS];
		public:
			cResult Initialization(const unsigned int i_maxComponents);
			void Update(const float i_elapsedSecondCount_systemTime, const float i_elapsedSecondCount_sinceLastSimulationUpdate);
			cResult CleanUp();
			cResult RegisterComponentSystem();
			//cResult RemoveComponentSystem();
			//ComponentSystem* GetComponents(unsigned int i_ID);
		};
	}
}


#endif
