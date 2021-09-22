// Includes
//=========

#include "cMyGame.h"

#include <Engine/Asserts/Asserts.h>
#include <Engine/UserInput/UserInput.h>

// Inherited Implementation
//=========================

// Run
//----

void eae6320::cMyGame::SubmitDataToBeRendered(const float i_elapsedSecondCount_systemTime, const float i_elapsedSecondCount_sinceLastSimulationUpdate) {
	Graphics::SetBackGroundColor(1.0f, 0.0f, 1.0f, 1.0f);
	Graphics::AddGeometryEffectPair(testGeometry, testEffect, 0);
	Graphics::AddGeometryEffectPair(testGeometry2, testEffect2, 1);
}

void eae6320::cMyGame::UpdateBasedOnInput()
{
	// Is the user pressing the ESC key?
	if ( UserInput::IsKeyPressed( UserInput::KeyCodes::Escape ) )
	{
		// Exit the application
		const auto result = Exit( EXIT_SUCCESS );
		EAE6320_ASSERT( result );
	}

	//pauses simulation
	if (UserInput::IsKeyPressed(UserInput::KeyCodes::Down))
	{
		eae6320::Application::iApplication::SetSimulationRate(0);
	}

	//resumes - sets it to regular speed
	if (UserInput::IsKeyPressed(UserInput::KeyCodes::Up))
	{
		eae6320::Application::iApplication::SetSimulationRate(1);
	}

	//fast forward
	if (UserInput::IsKeyPressed(UserInput::KeyCodes::Right))
	{
		eae6320::Application::iApplication::SetSimulationRate(2);
	}

	//slow mo
	if (UserInput::IsKeyPressed(UserInput::KeyCodes::Left))
	{
		eae6320::Application::iApplication::SetSimulationRate(.5);
	}

}

// Initialize / Clean Up
//----------------------

eae6320::cResult eae6320::cMyGame::Initialize()
{
	eae6320::Logging::OutputMessage("Initializing MyGame");
	auto result = Results::Success;
	
	// Initialize the shading data
	{
		if (!(result = InitializeShadingData()))
		{
			EAE6320_ASSERTF(false, "Can't initialize Graphics without the shading data");
			return result;
		}
	}
	// Initialize the geometry
	{
		if (!(result = InitializeGeometry()))
		{
			EAE6320_ASSERTF(false, "Can't initialize Graphics without the geometry data");
			return result;
		}
	}

	eae6320::Logging::OutputMessage("Finished Initializing MyGame");
	return result;
}

eae6320::cResult eae6320::cMyGame::CleanUp()
{
	eae6320::Logging::OutputMessage("Cleaning Up MyGame");

	//geometry cleanup
	testGeometry->DecrementReferenceCount();
	testGeometry2->DecrementReferenceCount();
	
	//shader cleanup
	testEffect->DecrementReferenceCount();
	testEffect2->DecrementReferenceCount();

	eae6320::Logging::OutputMessage("Finished Cleaning Up MyGame");
	return Results::Success;
}

eae6320::cResult eae6320::cMyGame::InitializeGeometry() {
	//first geometry
	eae6320::Graphics::VertexFormats::sVertex_mesh geometryVertexData[4];
	{
		geometryVertexData[0].x = 0.0f;
		geometryVertexData[0].y = 0.0f;
		geometryVertexData[0].z = 0.0f;

		geometryVertexData[1].x = 0.0f;
		geometryVertexData[1].y = 1.0f;
		geometryVertexData[1].z = 0.0f;

		geometryVertexData[2].x = 1.0f;
		geometryVertexData[2].y = 1.0f;
		geometryVertexData[2].z = 0.0f;

		geometryVertexData[3].x = 1.0f;
		geometryVertexData[3].y = 0.0f;
		geometryVertexData[3].z = 0.0f;
	}
	uint16_t indexData[6] = { 0, 1, 2, 0, 2, 3 };
	//{0, 3, 2, 0, 2, 1};

	auto result = eae6320::Graphics::Geometry::MakeGeometry(geometryVertexData, 4, indexData, 6, testGeometry);
	if (!result)
		return result;

	//second geometry
	eae6320::Graphics::VertexFormats::sVertex_mesh geometryVertexData2[5];
	{
		geometryVertexData2[0].x = -1.0f;
		geometryVertexData2[0].y = -1.0f;
		geometryVertexData2[0].z = 0.0f;

		geometryVertexData2[1].x = -1.0f;
		geometryVertexData2[1].y = 0.0f;
		geometryVertexData2[1].z = 0.0f;

		geometryVertexData2[2].x = -0.5f;
		geometryVertexData2[2].y = 0.5f;
		geometryVertexData2[2].z = 0.0f;

		geometryVertexData2[3].x = 0.0f;
		geometryVertexData2[3].y = 0.0f;
		geometryVertexData2[3].z = 0.0f;

		geometryVertexData2[4].x = 0.0f;
		geometryVertexData2[4].y = -1.0f;
		geometryVertexData2[4].z = 0.0f;
	}
	uint16_t indexData2[9] = { 0, 1, 3, 1, 2, 3, 0, 3, 4 };
	//{0, 3, 1, 1, 3, 2, 0, 4, 3};

	result = eae6320::Graphics::Geometry::MakeGeometry(geometryVertexData2, 5, indexData2, 9, testGeometry2);

	return result;
}

eae6320::cResult eae6320::cMyGame::InitializeShadingData() {
	auto result = eae6320::Graphics::Effect::MakeEffect("data/Shaders/Vertex/standard.shader", "data/Shaders/Fragment/animatedColor.shader", testEffect);
	if (!result)
		return result;

	result = eae6320::Graphics::Effect::MakeEffect("data/Shaders/Vertex/standard.shader", "data/Shaders/Fragment/standard.shader", testEffect2);

	return result;
}
