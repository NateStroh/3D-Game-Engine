#include "Geometry.h"

eae6320::cResult eae6320::Graphics::Geometry::MakeGeometry(eae6320::Graphics::VertexFormats::sVertex_mesh i_vertexData[], const unsigned int i_vertexCount, uint16_t i_indexData[], const unsigned int i_indexCount, Geometry*& o_geometry)  {
	auto result = eae6320::Results::Success;

	Geometry *geometry = new Geometry();
	result = geometry->Initialize(i_vertexData, i_vertexCount, i_indexData, i_indexCount);
	o_geometry = geometry;

	return result;
}

eae6320::Graphics::Geometry::~Geometry() {
	CleanUp();
}
