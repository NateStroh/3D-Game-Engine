#ifndef EAE6320_ENTITYCOMPONENTSYSTEM_H
#define EAE6320_ENTITYCOMPONENTSYSTEM_H

#include <Engine/Results/Results.h>

#include "Component.h"

namespace eae6320
{
	namespace ECS {
		class EntityComponentSystem
		{
		private:
			//Component m_allComponents[];
		public:
			cResult Initialization(const unsigned int i_maxComponents);
			void Update(const float i_elapsedSecondCount_systemTime, const float i_elapsedSecondCount_sinceLastSimulationUpdate);
			cResult CleanUp();
			cResult AddComponent();
			cResult RemoveComponent();
			Component* GetComponents(unsigned int i_ID);
		};
	}
}


#endif
