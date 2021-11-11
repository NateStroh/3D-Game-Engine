#ifndef EAE6320_GAMEOBJECT_H
#define EAE6320_GAMEOBJECT_H

#include <Engine/Graphics/Graphics.h>
#include <Engine/Graphics/Effect.h>
#include <Engine/Graphics/Geometry.h>
#include <Engine/Application/Entity.h>

#if defined( EAE6320_PLATFORM_WINDOWS )
#include <Engine/Windows/Includes.h>
#endif

namespace eae6320
{
	namespace Application
	{
		class GameObject : public Entity {
		public:
			eae6320::Graphics::Geometry* m_geometry;
			eae6320::Graphics::Effect* m_effect;

			void SubmitToBeRendered(const float i_elapsedSecondCount_systemTime, const float i_elapsedSecondCount_sinceLastSimulationUpdate);
			void UpdateRigidBody(const float i_elapsedSecondCount_sinceLastUpdate);
		private:


		};
	}
}

#endif