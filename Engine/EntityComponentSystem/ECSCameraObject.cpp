#include "ECSCameraObject.h"
#include <Engine/Math/Functions.h>
#include <Engine/Graphics/Graphics.h>

#include <Engine/EntityComponentSystem/PhysicsSystem.h>

eae6320::ECS::ECSCameraObject::ECSCameraObject() {
	m_rigidBody = SmartPointer<eae6320::Physics::sRigidBodyState>(new eae6320::Physics::sRigidBodyState());
	m_cameraData.verticalFieldOfView_inRadians = Math::ConvertDegreesToRadians(45.0f);
	m_cameraData.aspectRatio = 1.0f;
	m_cameraData.z_nearPlane = 0.1f;
	m_cameraData.z_farPlane = 500.0f;
	m_pointer = SmartPointer<ECS::ECSEntity>(new ECS::ECSEntity(*this));
}

eae6320::ECS::ECSCameraObject::~ECSCameraObject()
{
	
}

eae6320::cResult eae6320::ECS::ECSCameraObject::Init()
{
	cResult result = Results::Success;
	eae6320::ECS::PhysicsSystem::CreatePhysicsComponent(m_rigidBody, m_pointer);
	return result;
}

eae6320::cResult eae6320::ECS::ECSCameraObject::CleanUp()
{
	cResult result = Results::Success;
	eae6320::ECS::PhysicsSystem::RemovePhysicsComponent(m_pointer);
	return result;
}

void eae6320::ECS::ECSCameraObject::SubmitToBeRendered(const float i_elapsedSecondCount_systemTime, const float i_elapsedSecondCount_sinceLastSimulationUpdate) {
	auto predictedCameraTransform = (*m_rigidBody).PredictFutureTransform(i_elapsedSecondCount_sinceLastSimulationUpdate);
	Graphics::SetCamera(predictedCameraTransform, m_cameraData);
}