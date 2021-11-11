#ifndef EAE6320_COMPONENTSYSTEM_H
#define EAE6320_COMPONENTSYSTEM_H

#include <iostream>
#include <vector>

#include <Engine/Results/Results.h>
#include <Engine/EntityComponentSystem/ECSEntity.h>
#include "SmartPointer.h"

namespace eae6320
{
	namespace ECS {

		template<typename T>
		struct ComponentData {
			T m_componentData;
			WeakPointer<ECS::ECSEntity> m_entity;

			ComponentData(const ComponentData& other) : 
				m_entity(other.m_entity)
			{
				m_componentData = other.m_componentData;
			}

			ComponentData(T i_component, SmartPointer<ECSEntity> i_entity) : 
				m_entity(i_entity)
			{
				m_componentData = i_component;
			}
		};

		template<typename T>
		class ComponentSystem
		{
		private:
			//unsigned int m_componentID = 0;
			//unsigned int componentNum = 0;
		public:
			std::vector<SmartPointer<ComponentData<T>>> m_componentList;
			cResult AddComponentToList(T i_component, SmartPointer<ECSEntity> i_entity);
			cResult RemoveComponentFromList(SmartPointer<ECSEntity> i_entity);
			T* GetComponent(SmartPointer<ECSEntity> i_entity);
		};
	}
}

template<typename T>
eae6320::cResult eae6320::ECS::ComponentSystem<T>::AddComponentToList(T i_component, SmartPointer<ECSEntity> i_entity) {
	SmartPointer<ComponentData<T>> newComponent = SmartPointer<ComponentData<T>>(new ComponentData<T>(i_component, i_entity));
	m_componentList.push_back(newComponent);
	return eae6320::cResult();
}

template<typename T>
eae6320::cResult eae6320::ECS::ComponentSystem<T>::RemoveComponentFromList(SmartPointer<ECSEntity> i_entity) {
	for (int i = 0; i < m_componentList.size(); i++) {
		ComponentData<T> test = *m_componentList[i];
		if ((*(test.m_entity.CreateSmartPointer())) == (*i_entity)) {
			m_componentList.erase(m_componentList.begin()+i);
			return eae6320::Results::Success;
		}
	}
	return eae6320::Results::Failure;
}

template<typename T>
T* eae6320::ECS::ComponentSystem<T>::GetComponent(SmartPointer<ECSEntity> i_entity) {
	for(SmartPointer<ComponentData<T>> component : m_componentList) {
		ComponentData<T> test = *component;
		if ((*(test.m_entity.CreateSmartPointer())) == (*i_entity)) {
			return &((*component).m_componentData);
		}
	}
	return nullptr;
}

#endif