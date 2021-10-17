#ifndef EAE6320_MESH_H
#define EAE6320_MESH_H

#include "Configuration.h"
#include "VertexFormats.h"
#include <Engine/Assets/ReferenceCountedAssets.h>

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
		struct point
		{
			float x = 0;
			float y = 0;
			float z = 0;
		};

		struct GeometryMakeData{
			unsigned int m_indicesCount = 0;
			unsigned int m_verticesCount = 0;
			eae6320::Graphics::VertexFormats::sVertex_mesh* m_vertexData = nullptr;
			uint16_t* m_indexData = nullptr;

			void CleanUp() {
				delete[] m_vertexData;
				delete[] m_indexData;
			}
		};

		class Geometry
		{
		public:
			void Draw(); 

			static cResult MakeGeometry(eae6320::Graphics::VertexFormats::sVertex_mesh i_vertexData[], const unsigned int i_vertexCount, uint16_t i_indexData[], const unsigned int i_indexCount, Geometry*& o_geometry);
			static cResult MakeGeometry(std::string i_path, Geometry*& o_geometry);

			EAE6320_ASSETS_DECLAREREFERENCECOUNTINGFUNCTIONS();

		private:
			EAE6320_ASSETS_DECLAREDELETEDREFERENCECOUNTEDFUNCTIONS(Geometry);
			EAE6320_ASSETS_DECLAREREFERENCECOUNT();

			cResult Initialize(eae6320::Graphics::VertexFormats::sVertex_mesh i_vertexData[], const unsigned int i_vertexCount, uint16_t i_indexData[], const unsigned int i_indexCount);
			cResult CleanUp();

			Geometry() = default;
			~Geometry();

#if defined( EAE6320_PLATFORM_D3D )
			cVertexFormat* m_vertexFormat = nullptr;
			//// A vertex buffer holds the data for each vertex
			ID3D11Buffer* m_vertexBuffer = nullptr;
			ID3D11Buffer* m_indexBuffer = nullptr;
#elif defined( EAE6320_PLATFORM_GL )
			// A vertex buffer holds the data for each vertex
			GLuint m_vertexBufferId = 0;
			GLuint m_indexBufferId = 0;
			// A vertex array encapsulates the vertex data as well as the vertex input layout
			GLuint m_vertexArrayId = 0;
#endif
			unsigned int m_indexCount = 0;

		};
	}
}

#endif