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
			//struct to hold the data of a component and a weak pointer to the entity it belongs to
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
			//Max number of components a system can have
			static const unsigned int MAX_COMPONENTS = 500;
			//current number of components
			unsigned int componentNum = 0;
			//function for shifting elements of the array down - keeps the array packed on removal of item
			void ShiftArrayDown(int i_index);
		public:
			//Componenet array
			SmartPointer<ComponentData<T>> m_componentArray[MAX_COMPONENTS];

			//function for adding a new component to the component array - puts the component at componentNum in the component array, increments componentNum
			cResult AddComponentToList(T i_component, SmartPointer<ECSEntity> i_entity);
			
			//function for removing a component from the list - only removes an item if matches entities (returns failure if entity couldn't be found), 
			//	decrements componentNum, shifts array down to keep all components contiguous
			cResult RemoveComponentFromList(SmartPointer<ECSEntity> i_entity);
			
			//function for getting the component data of an system - returns nullptr if the entity doesn't have a component in the system
			T* GetComponent(SmartPointer<ECSEntity> i_entity);
			
			//function for getting the current number of components - helpful for looping through all active components in a system
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
	//loops through the rest of the array starting at i_index and moves it down, effectively overwriting data at i_index
	for (unsigned int i = i_index; i < componentNum-1; i++) {
		m_componentArray[i] = m_componentArray[i++];
	}
}

template<typename T>
eae6320::cResult eae6320::ECS::ComponentSystem<T>::AddComponentToList(T i_component, SmartPointer<ECSEntity> i_entity) {
	//make sure the array has room
	if (componentNum == MAX_COMPONENTS)
		return Results::Failure;

	//make the componentdata into a smart pointer and put it in the list
	SmartPointer<ComponentData<T>> newComponent = SmartPointer<ComponentData<T>>(new ComponentData<T>(i_component, i_entity));
	m_componentArray[componentNum] = newComponent;
	componentNum++;
	return eae6320::cResult();
}

template<typename T>
eae6320::cResult eae6320::ECS::ComponentSystem<T>::RemoveComponentFromList(SmartPointer<ECSEntity> i_entity) {
	for (unsigned int i = 0; i < componentNum; i++) {
		//create a smart pointer of the entity pointer so we can compare it to the entity passed in
		SmartPointer<ECSEntity> newSmartPointer = (((*m_componentArray[i]).m_entity.CreateSmartPointer()));
		//if they match shift the array down (deleting the item and keeping array contiguous) and decrement component num
		if (&(*newSmartPointer) == &(*i_entity)) {
			ShiftArrayDown(i);
			componentNum--;
			return eae6320::Results::Success;
		}
	}

	//if the entity wasn't found return failure
	return eae6320::Results::Failure;
}

template<typename T>
T* eae6320::ECS::ComponentSystem<T>::GetComponent(SmartPointer<ECSEntity> i_entity) {
	for (unsigned int i = 0; i < componentNum; i++) {
		//create a smart pointer of the entity pointer so we can compare it to the entity passed in
		SmartPointer<ECSEntity> newSmartPointer = (((*m_componentArray[i]).m_entity.CreateSmartPointer()));
		//if they match return the address of that component - allows them to make changes or copy it if they want
		if (&(*newSmartPointer) == &(*i_entity)) {
			return &((*m_componentArray[i]).m_componentData);
		}
	}

	return nullptr;
}

#endif