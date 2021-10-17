// Includes
//=========

#include "cMyGame.h"

#include <Engine/Asserts/Asserts.h>
#include <Engine/UserInput/UserInput.h>
#include <Engine/Math/cMatrix_transformation.h>

// Inherited Implementation
//=========================

// Run
//----

void eae6320::cMyGame::SubmitDataToBeRendered(const float i_elapsedSecondCount_systemTime, const float i_elapsedSecondCount_sinceLastSimulationUpdate) {
	Graphics::SetBackGroundColor(1.0f, 0.0f, 1.0f, 1.0f);

	if(shiftpressed){
		m_gameObject.m_geometry = geometryArray[2];
		m_gameObject.m_effect = effectArray[0];
	}
	else {
		m_gameObject.m_geometry = geometryArray[0];
		m_gameObject.m_effect = effectArray[1];
	}

	m_mainCamera.SubmitToBeRendered(i_elapsedSecondCount_systemTime, i_elapsedSecondCount_sinceLastSimulationUpdate);

	m_gameObject.SubmitToBeRendered(i_elapsedSecondCount_systemTime, i_elapsedSecondCount_sinceLastSimulationUpdate);
	m_gameObject2.SubmitToBeRendered(i_elapsedSecondCount_systemTime, i_elapsedSecondCount_sinceLastSimulationUpdate);
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
	if (UserInput::IsKeyPressed(UserInput::KeyCodes::Space)) {
		eae6320::Application::iApplication::SetSimulationRate(0);
	}
	else {
		eae6320::Application::iApplication::SetSimulationRate(1);
	}


}

void eae6320::cMyGame::UpdateSimulationBasedOnInput() {
	if (UserInput::IsKeyPressed(UserInput::KeyCodes::Space)) {
		spacepressed = true;
	}
	else {
		spacepressed = false;
	}
	if (UserInput::IsKeyPressed(UserInput::KeyCodes::Shift)) {
		shiftpressed = true;
	}
	else {
		shiftpressed = false;
	}

	if (UserInput::IsKeyPressed(UserInput::KeyCodes::Up)) {
		m_gameObject.m_rigidBody.velocity += { 0.0f, 1.0f, 0.0f };
	}
	if (UserInput::IsKeyPressed(UserInput::KeyCodes::Down)) {
		m_gameObject.m_rigidBody.velocity += { 0.0f, -1.0f, 0.0f };
	}
	if (UserInput::IsKeyPressed(UserInput::KeyCodes::Right)) {
		m_gameObject.m_rigidBody.velocity += { 1.0f, 0.0f, 0.0f };
	}
	if (UserInput::IsKeyPressed(UserInput::KeyCodes::Left)) {
		m_gameObject.m_rigidBody.velocity += { -1.0f, 0.0f, 0.0f };
	}

	if (UserInput::IsKeyPressed('W')) {
		m_mainCamera.m_rigidBody.velocity += { 0.0f, 1.0f, 0.0f };
	}
	if (UserInput::IsKeyPressed('S')) {
		m_mainCamera.m_rigidBody.velocity += { 0.0f, -1.0f, 0.0f };
	}
	if (UserInput::IsKeyPressed('D')) {
		m_mainCamera.m_rigidBody.velocity += { 1.0f, 0.0f, 0.0f };
	}
	if (UserInput::IsKeyPressed('A')) {
		m_mainCamera.m_rigidBody.velocity += { -1.0f, 0.0f, 0.0f };
	}
	if (UserInput::IsKeyPressed('X')) {
		m_mainCamera.m_rigidBody.velocity += { 0.0f, 0.0f, 1.0f };
	}
	if (UserInput::IsKeyPressed('Z')) {
		m_mainCamera.m_rigidBody.velocity += { 0.0f, 0.0f, -1.0f };
	}

}

void eae6320::cMyGame::UpdateSimulationBasedOnTime(const float i_elapsedSecondCount_sinceLastUpdate) {
	m_gameObject.UpdateRigidBody(i_elapsedSecondCount_sinceLastUpdate);
	m_mainCamera.UpdateRigidBody(i_elapsedSecondCount_sinceLastUpdate);
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

	m_gameObject.m_geometry = geometryArray[2];
	m_gameObject.m_effect = effectArray[0];
	m_gameObject.m_rigidBody;

	m_gameObject2.m_geometry = geometryArray[1];
	m_gameObject2.m_effect = effectArray[1];
	m_gameObject2.m_rigidBody;

	m_mainCamera.m_rigidBody.position = {0,0,5};

	eae6320::Logging::OutputMessage("Finished Initializing MyGame");
	return result;
}

eae6320::cResult eae6320::cMyGame::CleanUp()
{
	eae6320::Logging::OutputMessage("Cleaning Up MyGame");

	//geometry cleanup
	geometryArray[0]->DecrementReferenceCount();
	geometryArray[1]->DecrementReferenceCount();
	geometryArray[2]->DecrementReferenceCount();
	geometryArray[0] = nullptr;
	geometryArray[1] = nullptr;
	geometryArray[2] = nullptr;

	//shader cleanup
	effectArray[0]->DecrementReferenceCount();
	effectArray[1]->DecrementReferenceCount();
	effectArray[0] = nullptr;
	effectArray[1] = nullptr;

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

	auto result = eae6320::Graphics::Geometry::MakeGeometry(geometryVertexData, 4, indexData, 6, geometryArray[0]);
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

	result = eae6320::Graphics::Geometry::MakeGeometry(geometryVertexData2, 5, indexData2, 9, geometryArray[1]);
	result = eae6320::Graphics::Geometry::MakeGeometry("data/Meshes/geometrytest.lua", geometryArray[1]);

	//third mesh
	eae6320::Graphics::VertexFormats::sVertex_mesh geometryVertexData3[10];
	{
		geometryVertexData3[0].x = 0.0f;
		geometryVertexData3[0].y = 0.0f;
		geometryVertexData3[0].z = 0.0f;

		geometryVertexData3[1].x = 0.0f;
		geometryVertexData3[1].y = 1.0f;
		geometryVertexData3[1].z = 0.0f;
						  
		geometryVertexData3[2].x = 0.2f;
		geometryVertexData3[2].y = 1.0f;
		geometryVertexData3[2].z = 0.0f;
						  
		geometryVertexData3[3].x = 0.2f;
		geometryVertexData3[3].y = 0.8f;
		geometryVertexData3[3].z = 0.0f;
						  
		geometryVertexData3[4].x = 0.2f;
		geometryVertexData3[4].y = 0.0f;
		geometryVertexData3[4].z = 0.0f;
						  
		geometryVertexData3[5].x = 0.8f;
		geometryVertexData3[5].y = 0.0f;
		geometryVertexData3[5].z = 0.0f;
						  
		geometryVertexData3[6].x = 0.8f;
		geometryVertexData3[6].y = 0.2f;
		geometryVertexData3[6].z = 0.0f;
						  
		geometryVertexData3[7].x = 0.8f;
		geometryVertexData3[7].y = 1.0f;
		geometryVertexData3[7].z = 0.0f;
						  
		geometryVertexData3[8].x = 1.0f;
		geometryVertexData3[8].y = 1.0f;
		geometryVertexData3[8].z = 0.0f;
						  
		geometryVertexData3[9].x = 1.0f;
		geometryVertexData3[9].y = 0.0f;
		geometryVertexData3[9].z = 0.0f;
	}
	uint16_t indexData3[18] = { 0, 1, 2, 0, 2, 4,
								3, 2, 5, 5, 2, 6,
								5, 7, 8, 5, 8, 9 };

	result = eae6320::Graphics::Geometry::MakeGeometry(geometryVertexData3, 10, indexData3, 18, geometryArray[2]);

	return result;
}

eae6320::cResult eae6320::cMyGame::InitializeShadingData() {
	auto result = eae6320::Graphics::Effect::MakeEffect("data/Shaders/Vertex/standard.shader", "data/Shaders/Fragment/animatedColor.shader", effectArray[0]);
	if (!result)
		return result;

	result = eae6320::Graphics::Effect::MakeEffect("data/Shaders/Vertex/standard.shader", "data/Shaders/Fragment/standard.shader", effectArray[1]);

	return result;
}
