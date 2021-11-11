 // Includes
//=========

#include "cMyGame.h"

#include <Engine/Asserts/Asserts.h>
#include <Engine/UserInput/UserInput.h>
#include <Engine/Math/cMatrix_transformation.h>
#include <Engine/EntityComponentSystem/ECSTestSystem.h>
#include <Engine/EntityComponentSystem/ECSEntity.h>
#include <Engine/EntityComponentSystem/SmartPointer.h>

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
	m_gameObject3.SubmitToBeRendered(i_elapsedSecondCount_systemTime, i_elapsedSecondCount_sinceLastSimulationUpdate);
	
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

	if (UserInput::IsKeyPressed('Z')) {
		m_mainCamera.m_rigidBody.velocity += { 0.0f, 1.0f, 0.0f };
	}
	if (UserInput::IsKeyPressed('X')) {
		m_mainCamera.m_rigidBody.velocity += { 0.0f, -1.0f, 0.0f };
	}
	if (UserInput::IsKeyPressed('D')) {
		m_mainCamera.m_rigidBody.velocity += { 1.0f, 0.0f, 0.0f };
	}
	if (UserInput::IsKeyPressed('A')) {
		m_mainCamera.m_rigidBody.velocity += { -1.0f, 0.0f, 0.0f };
	}
	if (UserInput::IsKeyPressed('S')) {
		m_mainCamera.m_rigidBody.velocity += { 0.0f, 0.0f, 1.0f };
	}
	if (UserInput::IsKeyPressed('W')) {
		m_mainCamera.m_rigidBody.velocity += { 0.0f, 0.0f, -1.0f };
	}

	if (UserInput::IsKeyPressed('Q')) {
		m_mainCamera.m_rigidBody.angularSpeed = 1.0f;
	}
	else if (UserInput::IsKeyPressed('E')) {
		m_mainCamera.m_rigidBody.angularSpeed = -1.0f;
	}
	else {
		m_mainCamera.m_rigidBody.angularSpeed = 0.0f;
	}
}

void eae6320::cMyGame::UpdateSimulationBasedOnTime(const float i_elapsedSecondCount_sinceLastUpdate) {
	m_gameObject.UpdateRigidBody(i_elapsedSecondCount_sinceLastUpdate);
	m_gameObject2.UpdateRigidBody(i_elapsedSecondCount_sinceLastUpdate);
	m_gameObject3.UpdateRigidBody(i_elapsedSecondCount_sinceLastUpdate);
	m_mainCamera.UpdateRigidBody(i_elapsedSecondCount_sinceLastUpdate);
}

// Initialize / Clean Up
//----------------------

eae6320::cResult eae6320::cMyGame::Initialize()
{
	eae6320::Logging::OutputMessage("Initializing MyGame");
	auto result = Results::Success;

	ECS::ECSTestSystem ECSTest;
	ECSTest.Init();

	SmartPointer<ECS::ECSEntity> entity = SmartPointer<ECS::ECSEntity>(new ECS::ECSEntity());
	SmartPointer<ECS::ECSEntity> entity2 = SmartPointer<ECS::ECSEntity>(new ECS::ECSEntity());

	ECSTest.CreateTestComponent("test", entity);
	ECSTest.CreateTestComponent("asdfasdfasdf", entity2);

	ECSTest.Update(1,1);

	ECSTest.RemoveTestComponent(entity2);

	ECSTest.Update(1, 1);

	auto test = ECSTest.GetTestComponent(entity);

	auto test2 = ECSTest.GetTestComponent(entity2);

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

	m_gameObject3.m_geometry = geometryArray[2];
	m_gameObject3.m_effect = effectArray[0];
	m_gameObject3.m_rigidBody;

	m_mainCamera.m_rigidBody.position = {0,1,5};

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
	auto result = eae6320::Graphics::Geometry::MakeGeometry("data/Meshes/Sphere.mesh", geometryArray[0]);
	result = eae6320::Graphics::Geometry::MakeGeometry("data/Meshes/Plane.mesh", geometryArray[1]);
	result = eae6320::Graphics::Geometry::MakeGeometry("data/Meshes/ColoredCube.mesh", geometryArray[2]);
	//result = eae6320::Graphics::Geometry::MakeGeometry("data/Meshes/ColoredCube.mesh", geometryArray[3]);
	return result;
}

eae6320::cResult eae6320::cMyGame::InitializeShadingData() {
	auto result = eae6320::Graphics::Effect::MakeEffect("data/Shaders/Vertex/standard.shader", "data/Shaders/Fragment/animatedColor.shader", effectArray[0]);
	if (!result)
		return result;

	result = eae6320::Graphics::Effect::MakeEffect("data/Shaders/Vertex/standard.shader", "data/Shaders/Fragment/standard.shader", effectArray[1]);

	return result;
}
