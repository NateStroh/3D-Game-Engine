#include "Geometry.h"

#include <Engine/Results/Results.h>
#include <External/Lua/Includes.h>
#include <Engine/ScopeGuard/cScopeGuard.h>
#include <Engine/Logging/Logging.h>

namespace
{
	eae6320::cResult LoadTableValues(lua_State& io_luaState, eae6320::Graphics::GeometryMakeData* i_geometryData);

	eae6320::cResult LoadTableValues_vertices(lua_State& io_luaState, eae6320::Graphics::GeometryMakeData* i_geometryData);

	eae6320::cResult LoadTableValues_indices(lua_State& io_luaState, eae6320::Graphics::GeometryMakeData* i_geometryData);

	eae6320::cResult LoadAsset(const char* const i_path, eae6320::Graphics::GeometryMakeData* i_geometryData);

	float GetFloatField(lua_State* i_luaState, const char* i_key);

	uint8_t ConvertColorToByte(float i_colorVal);
}

eae6320::cResult eae6320::Graphics::Geometry::MakeGeometry(eae6320::Graphics::VertexFormats::sVertex_mesh i_vertexData[], const unsigned int i_vertexCount, uint16_t i_indexData[], const unsigned int i_indexCount, Geometry*& o_geometry)  {
	auto result = eae6320::Results::Success;

	Geometry *geometry = new Geometry();
	result = geometry->Initialize(i_vertexData, i_vertexCount, i_indexData, i_indexCount);
	o_geometry = geometry;

	return result;
}

eae6320::cResult eae6320::Graphics::Geometry::MakeGeometry(const char* i_path, Geometry*& o_geometry) {
	auto result = eae6320::Results::Success;
	GeometryMakeData sGeometryData;

	LoadAsset(i_path, &sGeometryData);

	if (sGeometryData.m_verticesCount > UINT16_MAX) {
		Logging::OutputError("Too many indices are present in following file: ");
		Logging::OutputError(i_path);

		sGeometryData.CleanUp();
		return Results::Failure;
	}

	Geometry* geometry = new Geometry();
	result = geometry->Initialize(
		sGeometryData.m_vertexPositionData, 
		sGeometryData.m_verticesCount,
		sGeometryData.m_indexData,
		sGeometryData.m_indicesCount
	);
	o_geometry = geometry;

	sGeometryData.CleanUp();

	return result;
}


eae6320::Graphics::Geometry::~Geometry() {
	CleanUp();
}


// Helper Function Definitions
//============================

namespace
{
	eae6320::cResult LoadTableValues(lua_State& io_luaState, eae6320::Graphics::GeometryMakeData* i_geometryData)
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

	eae6320::cResult LoadTableValues_vertices(lua_State& io_luaState, eae6320::Graphics::GeometryMakeData* i_geometryData) {
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

				i_geometryData->m_vertexPositionData[count].r= ConvertColorToByte(GetFloatField(&io_luaState, "Red"));
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
			eae6320::Logging::OutputError(luaL_typename(&io_luaState, -1));
			return result;
		}

		return result;
	}

	uint8_t ConvertColorToByte(float i_colorVal) {
		return (i_colorVal >= 1.0 ? 255 : (i_colorVal <= 0.0 ? 0 : (int)floor(i_colorVal * 256.0)));
	}

	float GetFloatField(lua_State* i_luaState, const char* i_key) {
		lua_pushstring(i_luaState, i_key);
		lua_gettable(i_luaState, -2);

		float result = static_cast<float>(lua_tonumber(i_luaState, -1));
		lua_pop(i_luaState, 1);
		return result;
	}

	eae6320::cResult LoadTableValues_indices(lua_State& io_luaState, eae6320::Graphics::GeometryMakeData* i_geometryData) {
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
			eae6320::Logging::OutputError(luaL_typename(&io_luaState, -1));
			return result;
		}

		return result;
	}

	eae6320::cResult LoadAsset(const char* const i_path, eae6320::Graphics::GeometryMakeData* i_geometryData)
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
				eae6320::Logging::OutputError("Failed to create a new Lua state\n");
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
				eae6320::Logging::OutputError(lua_tostring(luaState, -1));
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
						eae6320::Logging::OutputError(luaL_typename(luaState, -1));
						// Pop the returned non-table value
						lua_pop(luaState, 1);
						return result;
					}
				}
				else
				{
					result = eae6320::Results::InvalidFile;
					eae6320::Logging::OutputError("invalid file");

					// Pop every value that was returned
					lua_pop(luaState, returnedValueCount);
					return result;
				}
			}
			else
			{
				result = eae6320::Results::InvalidFile;
				eae6320::Logging::OutputError(lua_tostring(luaState, -1));

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
}


