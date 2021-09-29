#ifndef EAE6320_GAMEOBJECT_H
#define EAE6320_GAMEOBJECT_H

#include <Engine/Graphics/Graphics.h>
#include <Engine/Graphics/Effect.h>
#include <Engine/Graphics/Geometry.h>
#include <Engine/Physics/sRigidBodyState.h>

#if defined( EAE6320_PLATFORM_WINDOWS )
#include <Engine/Windows/Includes.h>
#endif

namespace eae6320
{
	namespace Application
	{
		class GameObject {
		public:
			eae6320::Graphics::Geometry* m_geometry;
			eae6320::Graphics::Effect* m_effect;
			eae6320::Physics::sRigidBodyState m_rigidBody;

		private:


		};
	}
}

#endif