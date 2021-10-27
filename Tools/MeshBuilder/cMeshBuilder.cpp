#include "cMeshBuilder.h"

#include <Tools/AssetBuildLibrary/Functions.h>

#include <Engine/Platform/Platform.h>
#include <Engine/ScopeGuard/cScopeGuard.h>
#include <fstream>

eae6320::cResult eae6320::Assets::cMeshBuilder::Build(const std::vector<std::string>& i_arguments) {
	eae6320::cResult result = Results::Success;
	
	GeometryMakeData makeData;
	LoadAsset(m_path_source, &makeData);

	if (makeData.m_verticesCount > UINT16_MAX) {
		eae6320::Assets::OutputErrorMessageWithFileInfo(m_path_source, "Too many vertices are in the file!\n");
		return Results::Failure;
	}

	FILE* oFile;
	oFile = fopen(m_path_target, "wb");
	if (oFile == 0) {
		eae6320::Assets::OutputErrorMessageWithFileInfo(m_path_source, "Failed to create file!\n");
		return Results::Failure;
	}
	
	fwrite(&makeData.m_verticesCount, sizeof(uint16_t), 1, oFile);
	fwrite(&makeData.m_indicesCount, sizeof(uint16_t), 1, oFile);
	fwrite(makeData.m_vertexPositionData, sizeof(eae6320::Graphics::VertexFormats::sVertex_mesh), makeData.m_verticesCount, oFile);
	fwrite(makeData.m_indexData, sizeof(uint16_t), makeData.m_indicesCount, oFile);

	if (fwrite == 0) {
		eae6320::Assets::OutputErrorMessageWithFileInfo(m_path_source, "Failed to write to file!\n");
		return Results::Failure;
	}

	fclose(oFile);

	makeData.CleanUp();
	return result;
}


eae6320::cResult eae6320::Assets::cMeshBuilder::LoadTableValues(lua_State& io_luaState, GeometryMakeData* i_geometryData)
{
	auto result = eae6320::Results::Success;

	if (!(result = LoadTableValues_vertices(io_luaState, i_geometryData)))
	{
		return result;
	}
	if (!(result = LoadTableValues_indices(io_luaState, i_geometryData)))
	{
		return result;
	}

	return result;
}

eae6320::cResult eae6320::Assets::cMeshBuilder::LoadTableValues_vertices(lua_State& io_luaState, GeometryMakeData* i_geometryData) {
	auto result = eae6320::Results::Success;
	unsigned int NumOfVertices;

	// Right now the asset table is at -1.
	// After the following table operation it will be at -2
	// and the "parameters" table will be at -1:
	constexpr auto* const key = "Vertices";
	lua_pushstring(&io_luaState, key);
	lua_gettable(&io_luaState, -2);
	eae6320::cScopeGuard scopeGuard_popParameters([&io_luaState]
		{
			lua_pop(&io_luaState, 1);
		});

	if (lua_istable(&io_luaState, -1)) {
		NumOfVertices = static_cast<unsigned int>(luaL_len(&io_luaState, -1));
		i_geometryData->m_verticesCount = NumOfVertices;
		i_geometryData->m_vertexPositionData = new eae6320::Graphics::VertexFormats::sVertex_mesh[i_geometryData->m_verticesCount];

		lua_pushnil(&io_luaState);
		unsigned int count = 0;
		//looping through all data in vertices - position, color, normal
		while (lua_next(&io_luaState, -2))
		{
			//------getting position
			constexpr auto* const key = "Position";
			lua_pushstring(&io_luaState, key);
			lua_gettable(&io_luaState, -2);
			eae6320::cScopeGuard scopeGuard_popPosition([&io_luaState]
				{
					lua_pop(&io_luaState, 1);
				});

			//getting x value
			lua_pushnumber(&io_luaState, 1);
			lua_gettable(&io_luaState, -2);
			i_geometryData->m_vertexPositionData[count].x = static_cast<float>(lua_tonumber(&io_luaState, -1));
			lua_pop(&io_luaState, 1);

			//getting y value
			lua_pushnumber(&io_luaState, 2);
			lua_gettable(&io_luaState, -2);
			i_geometryData->m_vertexPositionData[count].y = static_cast<float>(lua_tonumber(&io_luaState, -1));
			lua_pop(&io_luaState, 1);

			//getting z value
			lua_pushnumber(&io_luaState, 3);
			lua_gettable(&io_luaState, -2);
			i_geometryData->m_vertexPositionData[count].z = static_cast<float>(lua_tonumber(&io_luaState, -1));
			lua_pop(&io_luaState, 1);

			//------getting color
			lua_pushstring(&io_luaState, "Color");
			lua_gettable(&io_luaState, -3);
			eae6320::cScopeGuard scopeGuard_popColor([&io_luaState]
				{
					lua_pop(&io_luaState, 1);
				});

			i_geometryData->m_vertexPositionData[count].r = ConvertColorToByte(GetFloatField(&io_luaState, "Red"));
			i_geometryData->m_vertexPositionData[count].g = ConvertColorToByte(GetFloatField(&io_luaState, "Green"));
			i_geometryData->m_vertexPositionData[count].b = ConvertColorToByte(GetFloatField(&io_luaState, "Blue"));
			i_geometryData->m_vertexPositionData[count].a = ConvertColorToByte(GetFloatField(&io_luaState, "Alpha"));

			//------getting normal

			lua_pop(&io_luaState, 1);
			count++;
		}
	}
	else
	{
		result = eae6320::Results::InvalidFile;
		eae6320::Assets::OutputErrorMessageWithFileInfo(m_path_source, luaL_typename(&io_luaState, -1));
		return result;
	}

	return result;
}

uint8_t eae6320::Assets::cMeshBuilder::ConvertColorToByte(float i_colorVal) {
	return (i_colorVal >= 1.0 ? 255 : (i_colorVal <= 0.0 ? 0 : (int)floor(i_colorVal * 256.0)));
}

float eae6320::Assets::cMeshBuilder::GetFloatField(lua_State* i_luaState, const char* i_key) {
	lua_pushstring(i_luaState, i_key);
	lua_gettable(i_luaState, -2);

	float result = static_cast<float>(lua_tonumber(i_luaState, -1));
	lua_pop(i_luaState, 1);
	return result;
}

eae6320::cResult eae6320::Assets::cMeshBuilder::LoadTableValues_indices(lua_State& io_luaState, GeometryMakeData* i_geometryData) {
	auto result = eae6320::Results::Success;
	unsigned int NumOfIndices;

	// Right now the asset table is at -1.
	// After the following table operation it will be at -2
	// and the "parameters" table will be at -1:
	constexpr auto* const key = "Indices";
	lua_pushstring(&io_luaState, key);
	lua_gettable(&io_luaState, -2);
	eae6320::cScopeGuard scopeGuard_popParameters([&io_luaState]
		{
			lua_pop(&io_luaState, 1);
		});

	if (lua_istable(&io_luaState, -1)) {
		NumOfIndices = static_cast<unsigned int>(luaL_len(&io_luaState, -1));
		i_geometryData->m_indicesCount = NumOfIndices;
		i_geometryData->m_indexData = new uint16_t[i_geometryData->m_indicesCount];

		lua_pushnil(&io_luaState);
		unsigned int count = 0;
		//looping through indices
		while (lua_next(&io_luaState, -2))
		{
			i_geometryData->m_indexData[count] = static_cast<uint16_t>(lua_tointeger(&io_luaState, -1));
			lua_pop(&io_luaState, 1);
			count++;
		}

	}
	else
	{
		result = eae6320::Results::InvalidFile;
		eae6320::Assets::OutputErrorMessageWithFileInfo(m_path_source, luaL_typename(&io_luaState, -1));
		return result;
	}

	return result;
}

eae6320::cResult eae6320::Assets::cMeshBuilder::LoadAsset(const char* const i_path, GeometryMakeData* i_geometryData)
{
	auto result = eae6320::Results::Success;

	// Create a new Lua state
	lua_State* luaState = nullptr;
	eae6320::cScopeGuard scopeGuard_onExit([&luaState]
		{
			if (luaState)
			{
				// If I haven't made any mistakes
				// there shouldn't be anything on the stack
				// regardless of any errors
				EAE6320_ASSERT(lua_gettop(luaState) == 0);

				lua_close(luaState);
				luaState = nullptr;
			}
		});
	{
		luaState = luaL_newstate();
		if (!luaState)
		{
			result = eae6320::Results::OutOfMemory;
			eae6320::Assets::OutputErrorMessageWithFileInfo(m_path_source, "Failed to create a new Lua state\n");
			return result;
		}
	}

	// Load the asset file as a "chunk",
	// meaning there will be a callable function at the top of the stack
	const auto stackTopBeforeLoad = lua_gettop(luaState);
	{
		const auto luaResult = luaL_loadfile(luaState, i_path);
		if (luaResult != LUA_OK)
		{
			result = eae6320::Results::Failure;
			eae6320::Assets::OutputErrorMessageWithFileInfo(m_path_source, lua_tostring(luaState, -1));
			// Pop the error message
			lua_pop(luaState, 1);
			return result;
		}
	}
	// Execute the "chunk", which should load the asset
	// into a table at the top of the stack
	{
		constexpr int argumentCount = 0;
		constexpr int returnValueCount = LUA_MULTRET;	// Return _everything_ that the file returns
		constexpr int noMessageHandler = 0;
		const auto luaResult = lua_pcall(luaState, argumentCount, returnValueCount, noMessageHandler);
		if (luaResult == LUA_OK)
		{
			// A well-behaved asset file will only return a single value
			const auto returnedValueCount = lua_gettop(luaState) - stackTopBeforeLoad;
			if (returnedValueCount == 1)
			{
				// A correct asset file _must_ return a table
				if (!lua_istable(luaState, -1))
				{
					result = eae6320::Results::InvalidFile;
					eae6320::Assets::OutputErrorMessageWithFileInfo(m_path_source, luaL_typename(luaState, -1));
					// Pop the returned non-table value
					lua_pop(luaState, 1);
					return result;
				}
			}
			else
			{
				result = eae6320::Results::InvalidFile;
				eae6320::Assets::OutputErrorMessageWithFileInfo(m_path_source, "invalid file");

				// Pop every value that was returned
				lua_pop(luaState, returnedValueCount);
				return result;
			}
		}
		else
		{
			result = eae6320::Results::InvalidFile;
			eae6320::Assets::OutputErrorMessageWithFileInfo(m_path_source, lua_tostring(luaState, -1));

			// Pop the error message
			lua_pop(luaState, 1);
			return result;
		}
	}

	// If this code is reached the asset file was loaded successfully,
	// and its table is now at index -1
	eae6320::cScopeGuard scopeGuard_popAssetTable([luaState]
		{
			lua_pop(luaState, 1);
		});
	result = LoadTableValues(*luaState, i_geometryData);

	return result;
}
