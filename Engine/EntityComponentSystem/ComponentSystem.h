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
			static const unsigned int MAX_COMPONENTS = 500;
			unsigned int componentNum = 0;
			void ShiftArrayDown(int i_index);
		public:
			//std::vector<SmartPointer<ComponentData<T>>> m_componentList;
			SmartPointer<ComponentData<T>> m_componentArray[MAX_COMPONENTS];
			cResult AddComponentToList(T i_component, SmartPointer<ECSEntity> i_entity);
			cResult RemoveComponentFromList(SmartPointer<ECSEntity> i_entity);
			T* GetComponent(SmartPointer<ECSEntity> i_entity);
			unsigned int Size();
		};
	}
}

template<typename T>
unsigned int eae6320::ECS::ComponentSystem<T>::Size() {
	return componentNum;
}

template<typename T>
void eae6320::ECS::ComponentSystem<T>::ShiftArrayDown(int i_index) {
	for (unsigned int i = i_index; i < componentNum-1; i++) {
		m_componentArray[i] = m_componentArray[i++];
	}
}


template<typename T>
eae6320::cResult eae6320::ECS::ComponentSystem<T>::AddComponentToList(T i_component, SmartPointer<ECSEntity> i_entity) {
	if (componentNum == MAX_COMPONENTS)
		return Results::Failure;

	SmartPointer<ComponentData<T>> newComponent = SmartPointer<ComponentData<T>>(new ComponentData<T>(i_component, i_entity));
	//m_componentList.push_back(newComponent);
	m_componentArray[componentNum] = newComponent;
	componentNum++;
	return eae6320::cResult();
}

template<typename T>
eae6320::cResult eae6320::ECS::ComponentSystem<T>::RemoveComponentFromList(SmartPointer<ECSEntity> i_entity) {
	//for (unsigned int i = 0; i < m_componentList.size(); i++) {
	//	SmartPointer<ECSEntity> newSmartPointer = (((*m_componentList[i]).m_entity.CreateSmartPointer()));
	//	if ((&(*newSmartPointer)) == &(*i_entity)) {
	//		m_componentList.erase(m_componentList.begin()+i);
	//		return eae6320::Results::Success;
	//	}
	//}

	for (unsigned int i = 0; i < componentNum; i++) {
		SmartPointer<ECSEntity> newSmartPointer = (((*m_componentArray[i]).m_entity.CreateSmartPointer()));
		if (&(*newSmartPointer) == &(*i_entity)) {
			ShiftArrayDown(i);
			componentNum--;
			return eae6320::Results::Success;
		}
	}

	return eae6320::Results::Failure;
}

template<typename T>
T* eae6320::ECS::ComponentSystem<T>::GetComponent(SmartPointer<ECSEntity> i_entity) {
	//for(SmartPointer<ComponentData<T>> component : m_componentList) {
	//	SmartPointer<ECSEntity> newSmartPointer = (((*component).m_entity.CreateSmartPointer()));
	//	if (&(*newSmartPointer) == &(*i_entity)) {
	//		return &((*component).m_componentData);
	//	}
	//}

	for (unsigned int i = 0; i < componentNum; i++) {
		SmartPointer<ECSEntity> newSmartPointer = (((*m_componentArray[i]).m_entity.CreateSmartPointer()));
			if (&(*newSmartPointer) == &(*i_entity)) {
				return &((*m_componentArray[i]).m_componentData);
			}
	}

	return nullptr;
}

#endif