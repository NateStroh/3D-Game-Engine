#ifndef EAE6320_EFFECT_H
#define EAE6320_EFFECT_H

#include "Configuration.h"
#include "cRenderState.h"
#include "cShader.h"

#include <Engine/Assets/ReferenceCountedAssets.h>

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
			void Bind();

			static cResult MakeEffect(std::string i_vertexShaderLocation, std::string i_fragmentShaderLocation, Effect*& o_effect);

			EAE6320_ASSETS_DECLAREREFERENCECOUNTINGFUNCTIONS();

		private:
			EAE6320_ASSETS_DECLAREDELETEDREFERENCECOUNTEDFUNCTIONS(Effect);
			EAE6320_ASSETS_DECLAREREFERENCECOUNT();

			cResult Initialize(std::string i_vertexShaderLocation, std::string i_fragmentShaderLocation);
			cResult CleanUp();

			Effect() = default;
			~Effect();

			eae6320::Graphics::cShader* m_vertexShader = nullptr;
			eae6320::Graphics::cShader* m_fragmentShader = nullptr;
			eae6320::Graphics::cRenderState m_renderState;
#if defined( EAE6320_PLATFORM_GL )
			GLuint m_programId = 0;

			eae6320::cResult OpenGLInitilizaiton();
			eae6320::cResult OpenGLCleanUp();
#endif	
		};
	}
}

#endif