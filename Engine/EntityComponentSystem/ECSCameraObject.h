#ifndef EAE6320_ECSCAMERAOBJECT_H
#define EAE6320_ECSCAMERAOBJECT_H

#include "ECSEntity.h"
#include "Engine/Application/CameraObject.h"

namespace eae6320
{
	namespace ECS
	{
		//struct sCameraData {
		//	float verticalFieldOfView_inRadians;
		//	float aspectRatio;
		//	float z_nearPlane;
		//	float z_farPlane;
		//};

		class ECSCameraObject : public ECSEntity {
		private:

		public:
			eae6320::Application::sCameraData m_cameraData;
			ECSCameraObject();
			~ECSCameraObject();
			void SubmitToBeRendered(const float i_elapsedSecondCount_systemTime, const float i_elapsedSecondCount_sinceLastSimulationUpdate);
		};
	}
}

#endif