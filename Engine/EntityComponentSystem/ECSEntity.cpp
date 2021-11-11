#include "ECSEntity.h"

eae6320::cResult eae6320::ECS::ECSEntity::MakeEntity(ECSEntity*& o_entity)
{
	cResult result = Results::Success;
	ECSEntity* returnEntity = new ECSEntity();
	result = returnEntity->Initialize();
	o_entity = returnEntity;

	return result;
}

eae6320::cResult eae6320::ECS::ECSEntity::Initialize()
{
	cResult result = Results::Success;
	return result;
}

eae6320::cResult eae6320::ECS::ECSEntity::CleanUp()
{
	cResult result = Results::Success;
	return result;
}

eae6320::ECS::ECSEntity::ECSEntity()
{

}

eae6320::ECS::ECSEntity::~ECSEntity() {
	CleanUp();
}

bool eae6320::ECS::operator==(const ECSEntity& lhs, const ECSEntity& rhs)
{
	if (&lhs == &rhs) {
		return true;
	}
	else {
		return false;
	}
}
