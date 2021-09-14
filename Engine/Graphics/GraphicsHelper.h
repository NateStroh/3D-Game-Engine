#ifndef EAE6320_GRAPHICSHELPER_H
#define EAE6320_GRAPHICSHELPER_H

#include <Engine/Results/cResult.h>
#include <Engine/Asserts/Asserts.h>
#include <Engine/ScopeGuard/cScopeGuard.h>
#include <Engine/Logging/Logging.h>

namespace eae6320
{
	namespace Graphics
	{
		namespace GraphicsHelper {

			void ClearBackGroundBuffers();

			void Present();

			//cResult Initialize(const sInitializationParameters& i_initializationParameters);
			cResult Initialize(const unsigned int i_resolutionWidth, const unsigned int i_resolutionHeight);
			cResult CleanUp();
		}
	}
}

#endif