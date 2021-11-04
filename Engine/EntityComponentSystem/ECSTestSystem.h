#ifndef EAE6320_ECSTESTSYSTEM_H
#define EAE6320_ECSTESTSYSTEM_H

#include <Engine/EntityComponentSystem/ComponentSystem.h>
#include <string>

struct TestComponent {
	unsigned int id; 
	std::string m_test;
};

class ECSTestSystem : public eae6320::ECS::ComponentSystem {

};

#endif