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
		class cMeshBuilder final : public iBuilder
		{
			// Inherited Implementation
			//=========================

		private:

			// Build
			//------

			cResult Build(const std::vector<std::string>& i_arguments) final;

			eae6320::cResult LoadTableValues(lua_State& io_luaState, eae6320::Graphics::GeometryMakeData* i_geometryData);

			eae6320::cResult LoadTableValues_vertices(lua_State& io_luaState, eae6320::Graphics::GeometryMakeData* i_geometryData);

			eae6320::cResult LoadTableValues_indices(lua_State& io_luaState, eae6320::Graphics::GeometryMakeData* i_geometryData);

			eae6320::cResult LoadAsset(const char* const i_path, eae6320::Graphics::GeometryMakeData* i_geometryData);

			float GetFloatField(lua_State* i_luaState, const char* i_key);

			uint8_t ConvertColorToByte(float i_colorVal);
		};
	}
}

#endif
