#ifndef EAE6320_MESH_H
#define EAE6320_MESH_H

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
#include "cVertexFormat.h"
#elif defined( EAE6320_PLATFORM_GL )
#include "OpenGL/Includes.h"
#endif

namespace eae6320
{
	namespace Graphics
	{
		class Geometry
		{
		public:
			cResult Initialize();
			cResult CleanUp();

#if defined( EAE6320_PLATFORM_D3D )
			cVertexFormat* m_vertexFormat = nullptr;
			//// A vertex buffer holds the data for each vertex
			ID3D11Buffer* m_vertexBuffer = nullptr;
#elif defined( EAE6320_PLATFORM_GL )
			// A vertex buffer holds the data for each vertex
			GLuint m_vertexBufferId = 0;
			// A vertex array encapsulates the vertex data as well as the vertex input layout
			GLuint m_vertexArrayId = 0;
#endif

		private:


		};
	}
}

#endif