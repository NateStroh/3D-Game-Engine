#include "Geometry.h"

#include <Engine/Results/Results.h>
#include <External/Lua/Includes.h>
#include <Engine/ScopeGuard/cScopeGuard.h>
#include <Engine/Logging/Logging.h>
#include <Engine/Asserts/Asserts.h>


eae6320::cResult eae6320::Graphics::Geometry::MakeGeometry(eae6320::Graphics::VertexFormats::sVertex_mesh i_vertexData[], const unsigned int i_vertexCount, uint16_t i_indexData[], const unsigned int i_indexCount, Geometry*& o_geometry)  {
	auto result = eae6320::Results::Success;

	Geometry *geometry = new Geometry();
	result = geometry->Initialize(i_vertexData, i_vertexCount, i_indexData, i_indexCount);
	o_geometry = geometry;

	return result;
}

eae6320::cResult eae6320::Graphics::Geometry::MakeGeometry(const char* i_path, Geometry*& o_geometry) {
	auto result = eae6320::Results::Success;

	FILE* inFile = fopen(i_path, "rb");
	if (inFile == 0) {
		eae6320::Logging::OutputError("Invalid File - Couldn't open File: ");
		eae6320::Logging::OutputError(i_path);
		return eae6320::Results::Failure;
	}

	fseek(inFile, 0, SEEK_END);
	long size = ftell(inFile);
	rewind(inFile);

	char* buffer = (char*)malloc(size);
	size_t numRead = fread(buffer, sizeof(char), size, inFile);
	if (numRead == 0) {
		eae6320::Logging::OutputError("Didn't read anything: ");
		eae6320::Logging::OutputError(i_path);
		return eae6320::Results::Failure;
	}

	auto currentOffset = reinterpret_cast<uintptr_t>(buffer);
	const auto finalOffset = currentOffset + size;

	uint16_t vertexCount = *reinterpret_cast<uint16_t*>(currentOffset);
	currentOffset += sizeof(vertexCount);

	uint16_t indexCount = *reinterpret_cast<uint16_t*>(currentOffset);
	currentOffset += sizeof(indexCount);

	VertexFormats::sVertex_mesh* vertexArray = reinterpret_cast<VertexFormats::sVertex_mesh*>(currentOffset);
	currentOffset += (vertexCount * sizeof(VertexFormats::sVertex_mesh));

	uint16_t* indexArray = reinterpret_cast<uint16_t*>(currentOffset);
	currentOffset += (indexCount * sizeof(uint16_t));
	
	EAE6320_ASSERTF(currentOffset == finalOffset, "Filesize didn't line up.");

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

