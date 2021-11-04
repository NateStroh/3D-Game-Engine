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
			ComponentSystem* m_allComponentSystems;
			unsigned int MAX_COMPONENTS = 500;

		public:
			cResult Initialization(const unsigned int i_maxComponents);
			void Update(const float i_elapsedSecondCount_systemTime, const float i_elapsedSecondCount_sinceLastSimulationUpdate);
			cResult CleanUp();
			cResult AddComponentSystem();
			cResult RemoveComponentSystem();
			ComponentSystem* GetComponents(unsigned int i_ID);
		};
	}
}


#endif
