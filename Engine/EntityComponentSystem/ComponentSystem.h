#ifndef EAE6320_COMPONENTSYSTEM_H
#define EAE6320_COMPONENTSYSTEM_H

#include <iostream>
#include <vector>

#include <Engine/Results/Results.h>

namespace eae6320
{
	namespace ECS {
		template<typename T>
		class ComponentSystem
		{
		private:
			unsigned int m_componentID = 0;
			unsigned int componentNum = 0;
		public:
			std::vector<T> m_componentList;
			//void Update(const float i_elapsedSecondCount_systemTime, const float i_elapsedSecondCount_sinceLastSimulationUpdate);
			cResult AddComponentToList(T i_component);
			cResult RemoveComponentFromList(T i_component);
			T* GetComponenet(unsigned int i_ID);
		};
	}
}

template<typename T>
eae6320::cResult eae6320::ECS::ComponentSystem<T>::AddComponentToList(T i_component) {
	return eae6320::cResult();
}

template<typename T>
eae6320::cResult eae6320::ECS::ComponentSystem<T>::RemoveComponentFromList(T i_component) {
	return eae6320::cResult();
}

template<typename T>
T* eae6320::ECS::ComponentSystem<T>::GetComponenet(unsigned int i_ID) {
	return nullptr;
}

#endif