#ifndef EAE6320_ECSGAMEOBJECT_H
#define EAE6320_ECSGAMEOBJECT_H

#include "ECSEntity.h"

#include <Engine/Graphics/Geometry.h>
#include <Engine/Graphics/Effect.h>

namespace eae6320
{
	namespace ECS
	{
		class ECSGameObject : public ECSEntity {
		private:
			
		public:
			SmartPointer<ECS::ECSEntity> m_pointer;
			ECSGameObject();
			ECSGameObject(eae6320::Graphics::Geometry* i_geometry, eae6320::Graphics::Effect* i_effect);
			~ECSGameObject();
		};
	}
}

#endif