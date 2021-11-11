#ifndef EAE6320_ECSENTITY_H
#define EAE6320_ECSENTITY_H

#include <Engine/Physics/sRigidBodyState.h>
#include <Engine/Results/Results.h>

#if defined( EAE6320_PLATFORM_WINDOWS )
#include <Engine/Windows/Includes.h>
#endif

namespace eae6320
{
	namespace ECS
	{
		class ECSEntity {
		public:
			eae6320::Physics::sRigidBodyState m_rigidBody;

			static cResult MakeEntity(ECSEntity*& o_entity);

			ECSEntity();
			~ECSEntity();

			bool friend operator==(const ECSEntity& lhs, const ECSEntity& rhs);

		private:
			cResult Initialize();
			cResult CleanUp();

		};
	}
}

#endif
