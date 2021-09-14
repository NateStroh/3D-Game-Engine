#ifndef EAE6320_GRAPHICSHELPER_H
#define EAE6320_GRAPHICSHELPER_H

#include <Engine/Results/cResult.h>
#include <Engine/Asserts/Asserts.h>
#include <Engine/ScopeGuard/cScopeGuard.h>
#include <Engine/Logging/Logging.h>

#include "Graphics.h"

namespace eae6320
{
	namespace Graphics
	{
		namespace GraphicsHelper {

			void ClearBackGroundBuffers(float i_rValue = 0, float i_gValue = 0, float i_bValue = 0, float i_aValue = 1);

			void Present();

			cResult Initialize(const sInitializationParameters& i_initializationParameters);
			cResult CleanUp();
		}
	}
}

#endif