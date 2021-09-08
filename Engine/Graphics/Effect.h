#ifndef EAE6320_EFFECT_H
#define EAE6320_EFFECT_H

#include "Configuration.h"
#include "cConstantBuffer.h"
#include "ConstantBufferFormats.h"
#include "cRenderState.h"
#include "cShader.h"
#include "sContext.h"
#include "VertexFormats.h"

#if defined( EAE6320_PLATFORM_WINDOWS )
#include <Engine/Windows/Includes.h>
#endif

#if defined( EAE6320_PLATFORM_D3D )
#include "Direct3D/Includes.h"
#elif defined( EAE6320_PLATFORM_GL )
#include "OpenGL/Includes.h"
#endif

namespace eae6320
{
	namespace Graphics
	{
		class Effect
		{
		public:
#if defined( EAE6320_PLATFORM_D3D )
			eae6320::Graphics::cShader* m_vertexShader = nullptr;
			eae6320::Graphics::cShader* m_fragmentShader = nullptr;

			eae6320::Graphics::cRenderState m_renderState;
#elif defined( EAE6320_PLATFORM_GL )
			eae6320::Graphics::cShader* m_vertexShader = nullptr;
			eae6320::Graphics::cShader* m_fragmentShader = nullptr;
			GLuint m_programId = 0;

			eae6320::Graphics::cRenderState m_renderState;

			

#endif
			cResult Initialize(std::string i_vertexShaderLocation, std::string i_fragmentShaderLocation);
			cResult CleanUp();
			void Bind(
#if defined( EAE6320_PLATFORM_D3D )
				ID3D11DeviceContext* const i_direct3dImmediateContext
#endif
			);

		private:
			eae6320::cResult OpenGLInitilizaiton();
			eae6320::cResult OpenGLCleanUp();
		};
	}
}

#endif