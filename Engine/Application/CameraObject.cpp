#include "CameraObject.h"

#include <Engine/Math/Functions.h>

eae6320::Application::CameraObject::CameraObject() {
	eae6320::Physics::sRigidBodyState m_rigidBody;
	eae6320::Application::CameraObject::m_cameraData.verticalFieldOfView_inRadians = Math::ConvertDegreesToRadians(45.0f);
	eae6320::Application::CameraObject::m_cameraData.aspectRatio = 1.0f;
	eae6320::Application::CameraObject::m_cameraData.z_nearPlane = 0.1f;
	eae6320::Application::CameraObject::m_cameraData.z_farPlane = 10.0f;
}
