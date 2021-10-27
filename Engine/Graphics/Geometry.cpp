#include "Geometry.h"

#include <Engine/Results/Results.h>
#include <External/Lua/Includes.h>
#include <Engine/ScopeGuard/cScopeGuard.h>
#include <Engine/Logging/Logging.h>
#include <Engine/Asserts/Asserts.h>

namespace
{
	eae6320::cResult LoadFromBinary(const char* i_path, eae6320::Graphics::GeometryMakeData* o_makeData);
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

	FILE* inFile = fopen(i_path, "r");
	if (inFile == 0) {
		eae6320::Logging::OutputError("Invalid File - Couldn't open File: ");
		eae6320::Logging::OutputError(i_path);
		return eae6320::Results::Failure;
	}

	fseek(inFile, 0, SEEK_END);
	long size = ftell(inFile);
	rewind(inFile);

	char* buffer = (char*)malloc(size);
	fread(buffer, sizeof(char), size, inFile);

	auto currentOffset = reinterpret_cast<uintptr_t>(buffer);
	const auto finalOffset = currentOffset + size;

	uint16_t vertexCount = *reinterpret_cast<uint16_t*>(currentOffset);
	currentOffset += sizeof(vertexCount);
	uint16_t indexCount = *reinterpret_cast<uint16_t*>(currentOffset);

	currentOffset += sizeof(indexCount);
	VertexFormats::sVertex_mesh* const vertexArray = reinterpret_cast<VertexFormats::sVertex_mesh*>(currentOffset);

	currentOffset += (vertexCount * sizeof(VertexFormats::sVertex_mesh));
	uint16_t* const indexArray = reinterpret_cast<uint16_t*>(currentOffset);
	
	currentOffset += (indexCount * sizeof(uint16_t));
	EAE6320_ASSERTF(currentOffset == finalOffset, "Filesize didn't line up.");

	if (vertexCount > UINT16_MAX) {
		Logging::OutputError("Too many indices are present in following file: ");
		Logging::OutputError(i_path);
		return Results::Failure;
	}

	Geometry* geometry = new Geometry();
	result = geometry->Initialize(
		vertexArray,
		vertexCount,
		indexArray,
		indexCount
	);

	o_geometry = geometry;

	free(buffer);

	return result;
}


eae6320::Graphics::Geometry::~Geometry() {
	CleanUp();
}


namespace
{
	eae6320::cResult LoadFromBinary(const char* i_path, eae6320::Graphics::GeometryMakeData* o_makeData) {
		auto result = eae6320::Results::Success;

		FILE* inFile = fopen(i_path, "r");
		if (inFile == 0) {
			eae6320::Logging::OutputError("Invalid File - Couldn't open File: ");
			eae6320::Logging::OutputError(i_path);
			return eae6320::Results::Failure;
		}

		auto currentOffset = reinterpret_cast<uintptr_t>(inFile);
		fseek(inFile, 0L, SEEK_END);
		const auto finalOffset = ftell(inFile);
		fseek(inFile, 0L, SEEK_SET);

		const auto vertexCount = *reinterpret_cast<uint16_t*>(currentOffset);
		currentOffset += sizeof(vertexCount);
		const auto indexCount = *reinterpret_cast<uint16_t*>(currentOffset);

		currentOffset += sizeof(indexCount);
		auto* const vertexArray = reinterpret_cast<eae6320::Graphics::VertexFormats::sVertex_mesh*>(currentOffset);

		currentOffset += (vertexCount * sizeof(eae6320::Graphics::VertexFormats::sVertex_mesh));
		auto* const indexArray = reinterpret_cast<uint16_t*>(currentOffset);


		o_makeData->m_verticesCount = vertexCount;
		o_makeData->m_indicesCount = indexCount;
		o_makeData->m_vertexPositionData = vertexArray;
		o_makeData->m_indexData = indexArray;

		return result;
	}
}


