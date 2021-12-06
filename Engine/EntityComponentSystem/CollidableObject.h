#ifndef EAE6320_COLLIDABLEOBJECT_H
#define EAE6320_COLLIDABLEOBJECT_H

#include "ECSEntity.h"

#include <Engine/Graphics/Geometry.h>
#include <Engine/Graphics/Effect.h>
#include <Engine/Collision/Collision.h>

namespace eae6320
{
	namespace ECS
	{
		class CollidableObject : public ECSEntity {
		private:

		public:
			SmartPointer<ECS::ECSEntity> m_pointer;
			eae6320::Collision::cCollider* m_collider;
			CollidableObject();
			CollidableObject(eae6320::Graphics::Geometry* i_geometry, eae6320::Graphics::Effect* i_effect);
			~CollidableObject();
			cResult Init(eae6320::Graphics::Geometry* i_geometry, eae6320::Graphics::Effect* i_effect, Math::sVector i_extents, bool isTrigger, float i_drag = 0.1f, float i_maxSpeed = 1000.0f);
			cResult CleanUp();
		};
	}
}

#endif