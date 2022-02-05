#ifndef EAE6320_CAMERAOBJECT_H
#define EAE6320_CAMERAOBJECT_H

#include <Engine/Application/Entity.h>

#include <Engine/Math/Functions.h>
#if defined( EAE6320_PLATFORM_WINDOWS )
#include <Engine/Windows/Includes.h>
#endif

namespace eae6320
{
	namespace Application
	{
		struct sCameraData {
			float verticalFieldOfView_inRadians;
			float aspectRatio;
			float z_nearPlane;
			float z_farPlane;
		};

		class CameraObject : public Entity {
		public: 
			sCameraData m_cameraData;

			CameraObject();

			void SubmitToBeRendered(const float i_elapsedSecondCount_systemTime, const float i_elapsedSecondCount_sinceLastSimulationUpdate);
			void UpdateRigidBody(const float i_elapsedSecondCount_sinceLastUpdate);
		private:


		};
	}
}

#endif