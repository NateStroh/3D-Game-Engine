#include "ECSCameraObject.h"
#include <Engine/Math/Functions.h>
#include <Engine/Graphics/Graphics.h>

eae6320::ECS::ECSCameraObject::ECSCameraObject() {
	m_rigidBody = SmartPointer<eae6320::Physics::sRigidBodyState>(new eae6320::Physics::sRigidBodyState());
	m_cameraData.verticalFieldOfView_inRadians = Math::ConvertDegreesToRadians(45.0f);
	m_cameraData.aspectRatio = 1.0f;
	m_cameraData.z_nearPlane = 0.1f;
	m_cameraData.z_farPlane = 50.0f;
}

eae6320::ECS::ECSCameraObject::~ECSCameraObject()
{

}

void eae6320::ECS::ECSCameraObject::SubmitToBeRendered(const float i_elapsedSecondCount_systemTime, const float i_elapsedSecondCount_sinceLastSimulationUpdate) {
	auto predictedCameraTransform = (*m_rigidBody).PredictFutureTransform(i_elapsedSecondCount_sinceLastSimulationUpdate);
	Graphics::SetCamera(predictedCameraTransform, m_cameraData);
}