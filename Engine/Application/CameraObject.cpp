#include "CameraObject.h"

#include <Engine/Math/Functions.h>
#include <Engine/Graphics/Graphics.h>

eae6320::Application::CameraObject::CameraObject() {
	eae6320::Physics::sRigidBodyState m_rigidBody;
	eae6320::Application::CameraObject::m_cameraData.verticalFieldOfView_inRadians = Math::ConvertDegreesToRadians(45.0f);
	eae6320::Application::CameraObject::m_cameraData.aspectRatio = 1.0f;
	eae6320::Application::CameraObject::m_cameraData.z_nearPlane = 0.1f;
	eae6320::Application::CameraObject::m_cameraData.z_farPlane = 50.0f;
}

void eae6320::Application::CameraObject::SubmitToBeRendered(const float i_elapsedSecondCount_systemTime, const float i_elapsedSecondCount_sinceLastSimulationUpdate) {
	auto predictedCameraTransform = m_rigidBody.PredictFutureTransform(i_elapsedSecondCount_sinceLastSimulationUpdate);
	Graphics::SetCamera(predictedCameraTransform, m_cameraData);
}

void eae6320::Application::CameraObject::UpdateRigidBody(const float i_elapsedSecondCount_sinceLastUpdate) {
	m_rigidBody.Update(i_elapsedSecondCount_sinceLastUpdate);
}
