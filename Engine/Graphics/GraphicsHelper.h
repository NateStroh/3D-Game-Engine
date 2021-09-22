#ifndef EAE6320_GRAPHICSHELPER_H
#define EAE6320_GRAPHICSHELPER_H

#include "Graphics.h"

namespace eae6320
{
	namespace Graphics
	{
		namespace GraphicsHelper {

			void ClearBackGroundBuffers(float i_rValue = 0, float i_gValue = 0, float i_bValue = 0, float i_aValue = 1);

			void ClearBackGroundBuffers(Graphics::sColor i_color);

			void Present();

			cResult Initialize(const sInitializationParameters& i_initializationParameters);
			cResult CleanUp();
		}
	}
}

#endif