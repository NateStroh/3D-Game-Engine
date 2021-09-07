#include "../Geometry.h"
#include <Engine/Logging/Logging.h>

//instantiations
namespace 
{
	//eae6320::Graphics::cVertexFormat* m_vertexFormat = nullptr;
	//// A vertex buffer holds the data for each vertex
	//ID3D11Buffer* m_vertexBuffer = nullptr;

	eae6320::Graphics::cVertexFormat* GetVertexFormat();
	void SetVertexFormat(eae6320::Graphics::cVertexFormat* i_vertexFormat);

	ID3D11Buffer* GetVertexBuffer();
	void SetVertexBuffer(ID3D11Buffer* i_vertexBuffer);

}

eae6320::cResult eae6320::Graphics::Geometry::Initialize(eae6320::Graphics::point vertex0, eae6320::Graphics::point vertex1, eae6320::Graphics::point vertex2) {
	auto result = eae6320::Results::Success;

	auto* const direct3dDevice = eae6320::Graphics::sContext::g_context.direct3dDevice;
	EAE6320_ASSERT(direct3dDevice);

	// Vertex Format
	{
		if (!(result = eae6320::Graphics::cVertexFormat::Load(eae6320::Graphics::eVertexType::Mesh, m_vertexFormat,
			"data/Shaders/Vertex/vertexInputLayout_mesh.shader")))
		{
			EAE6320_ASSERTF(false, "Can't initialize geometry without vertex format");
			return result;
		}
	}
	// Vertex Buffer
	{
		constexpr unsigned int triangleCount = 1;
		constexpr unsigned int vertexCountPerTriangle = 3;
		constexpr auto vertexCount = triangleCount * vertexCountPerTriangle;
		eae6320::Graphics::VertexFormats::sVertex_mesh vertexData[vertexCount];
		{
			// Direct3D is left-handed

			vertexData[0].x = vertex0.x;
			vertexData[0].y = vertex0.y;
			vertexData[0].z = vertex0.z;

			vertexData[1].x = vertex1.x;
			vertexData[1].y = vertex1.y;
			vertexData[1].z = vertex1.z;

			vertexData[2].x = vertex2.x;
			vertexData[2].y = vertex2.y;
			vertexData[2].z = vertex2.z;
		}
		constexpr auto bufferSize = sizeof(vertexData[0]) * vertexCount;
		EAE6320_ASSERT(bufferSize <= std::numeric_limits<decltype(D3D11_BUFFER_DESC::ByteWidth)>::max());
		constexpr auto bufferDescription = [bufferSize]
		{
			D3D11_BUFFER_DESC bufferDescription{};

			bufferDescription.ByteWidth = static_cast<unsigned int>(bufferSize);
			bufferDescription.Usage = D3D11_USAGE_IMMUTABLE;	// In our class the buffer will never change after it's been created
			bufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bufferDescription.CPUAccessFlags = 0;	// No CPU access is necessary
			bufferDescription.MiscFlags = 0;
			bufferDescription.StructureByteStride = 0;	// Not used

			return bufferDescription;
		}();

		const auto initialData = [vertexData]
		{
			D3D11_SUBRESOURCE_DATA initialData{};

			initialData.pSysMem = vertexData;
			// (The other data members are ignored for non-texture buffers)

			return initialData;
		}();

		const auto result_create = direct3dDevice->CreateBuffer(&bufferDescription, &initialData, &m_vertexBuffer);
		if (FAILED(result_create))
		{
			result = eae6320::Results::Failure;
			EAE6320_ASSERTF(false, "3D object vertex buffer creation failed (HRESULT %#010x)", result_create);
			eae6320::Logging::OutputError("Direct3D failed to create a 3D object vertex buffer (HRESULT %#010x)", result_create);
			return result;
		}
	}

	return result;
}

eae6320::cResult eae6320::Graphics::Geometry::CleanUp() {
	auto result = Results::Success;
	
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = nullptr;
	}
	if (m_vertexFormat)
	{
		m_vertexFormat->DecrementReferenceCount();
		m_vertexFormat = nullptr;
	}

	return result;
}

//definitions 
//namespace {
//	eae6320::Graphics::cVertexFormat* GetVertexFormat()
//	{
//		return m_vertexFormat;
//	}
//
//	void SetVertexFormat(eae6320::Graphics::cVertexFormat* i_vertexFormat)
//	{ 
//		m_vertexFormat = i_vertexFormat;
//	}
//
//	ID3D11Buffer* GetVertexBuffer()
//	{
//		return m_vertexBuffer;
//	}
//
//	void SetVertexBuffer(ID3D11Buffer* i_vertexBuffer)
//	{
//		m_vertexBuffer = i_vertexBuffer;
//	}
//}