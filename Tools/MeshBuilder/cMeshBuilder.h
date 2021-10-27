/*
	This class builds Meshes/Geometry
*/

#ifndef EAE6320_CMESHBUILDER_H
#define EAE6320_CMESHBUILDER_H

// Includes
//=========

#include <Tools/AssetBuildLibrary/iBuilder.h>
#include <Engine/Graphics/Geometry.h>
#include <External/Lua/Includes.h>

// Class Declaration
//==================

namespace eae6320
{
	namespace Assets
	{
		struct GeometryMakeData {
			unsigned int m_indicesCount = 0;
			unsigned int m_verticesCount = 0;
			eae6320::Graphics::VertexFormats::sVertex_mesh* m_vertexPositionData = nullptr;
			uint16_t* m_indexData = nullptr;

			void CleanUp() {
				delete[] m_vertexPositionData;
				delete[] m_indexData;
			}
		};

		class cMeshBuilder final : public iBuilder
		{
			// Inherited Implementation
			//=========================

		private:
			// Build
			//------

			cResult Build(const std::vector<std::string>& i_arguments) final;

			eae6320::cResult LoadTableValues(lua_State& io_luaState, GeometryMakeData* i_geometryData);

			eae6320::cResult LoadTableValues_vertices(lua_State& io_luaState, GeometryMakeData* i_geometryData);

			eae6320::cResult LoadTableValues_indices(lua_State& io_luaState, GeometryMakeData* i_geometryData);

			eae6320::cResult LoadAsset(const char* const i_path, GeometryMakeData* i_geometryData);

			float GetFloatField(lua_State* i_luaState, const char* i_key);

			uint8_t ConvertColorToByte(float i_colorVal);
		};
	}
}

#endif
