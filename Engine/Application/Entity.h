#ifndef EAE6320_ENTITY_H
#define EAE6320_ENTITY_H

#include <Engine/Physics/sRigidBodyState.h>
#include <Engine/Math/Functions.h>
#if defined( EAE6320_PLATFORM_WINDOWS )
#include <Engine/Windows/Includes.h>
#endif

namespace eae6320
{
	namespace Application
	{
		class Entity {
		public:
			eae6320::Physics::sRigidBodyState m_rigidBody;

		private:

		};
	}
}

#endif