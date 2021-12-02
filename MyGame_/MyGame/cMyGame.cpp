 // Includes
//=========

#include "cMyGame.h"

#include <Engine/Asserts/Asserts.h>
#include <Engine/UserInput/UserInput.h>
#include <Engine/Math/cMatrix_transformation.h>
#include <Engine/EntityComponentSystem/ECSTestSystem.h>
#include <Engine/EntityComponentSystem/SmartPointer.h>

// Inherited Implementation
//=========================

// Run
//----

void eae6320::cMyGame::SubmitDataToBeRendered(const float i_elapsedSecondCount_systemTime, const float i_elapsedSecondCount_sinceLastSimulationUpdate) {
	Graphics::SetBackGroundColor(1.0f, 0.0f, 1.0f, 1.0f);

	if(shiftpressed){
		eae6320::ECS::RenderComponent::ChangeGeometry(geometryArray[0], effectArray[1], gameObject.m_pointer);
	}
	else {
		eae6320::ECS::RenderComponent::ChangeGeometry(geometryArray[2], effectArray[0], gameObject.m_pointer);
	}
	
	camera.SubmitToBeRendered(i_elapsedSecondCount_systemTime, i_elapsedSecondCount_sinceLastSimulationUpdate);

	eae6320::ECS::RenderComponent::Update(i_elapsedSecondCount_systemTime, i_elapsedSecondCount_sinceLastSimulationUpdate);

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
		gameObject.m_rigidBody.operator*().velocity += { 0.0f, 1.0f, 0.0f };
	}
	if (UserInput::IsKeyPressed(UserInput::KeyCodes::Down)) {
		gameObject.m_rigidBody.operator*().velocity += { 0.0f, -1.0f, 0.0f };
	}
	if (UserInput::IsKeyPressed(UserInput::KeyCodes::Right)) {
		gameObject.m_rigidBody.operator*().velocity += { 1.0f, 0.0f, 0.0f };
	}
	if (UserInput::IsKeyPressed(UserInput::KeyCodes::Left)) {
		gameObject.m_rigidBody.operator*().velocity += { -1.0f, 0.0f, 0.0f };
	}

	if (UserInput::IsKeyPressed('Z')) {
		camera.m_rigidBody.operator*().velocity += { 0.0f, 1.0f, 0.0f };
	}
	if (UserInput::IsKeyPressed('X')) {
		camera.m_rigidBody.operator*().velocity += { 0.0f, -1.0f, 0.0f };
	}
	if (UserInput::IsKeyPressed('D')) {
		camera.m_rigidBody.operator*().velocity += { 1.0f, 0.0f, 0.0f };
	}
	if (UserInput::IsKeyPressed('A')) {
		camera.m_rigidBody.operator*().velocity += { -1.0f, 0.0f, 0.0f };
	}
	if (UserInput::IsKeyPressed('S')) {
		camera.m_rigidBody.operator*().velocity += { 0.0f, 0.0f, 1.0f };
	}
	if (UserInput::IsKeyPressed('W')) {
		camera.m_rigidBody.operator*().velocity += { 0.0f, 0.0f, -1.0f };
	}

	if (UserInput::IsKeyPressed('Q')) {
		camera.m_rigidBody.operator*().angularSpeed = 1.0f;
		SmartPointer<eae6320::Physics::sRigidBodyState> rigidBody = (*entity2).m_rigidBody;
		(*rigidBody).angularSpeed = 1.0f;
	}
	else if (UserInput::IsKeyPressed('E')) {
		camera.m_rigidBody.operator*().angularSpeed = -1.0f;
	}
	else {
		camera.m_rigidBody.operator*().angularSpeed = 0.0f;
	}
}

void eae6320::cMyGame::UpdateSimulationBasedOnTime(const float i_elapsedSecondCount_sinceLastUpdate) {
	eae6320::ECS::PhysicsSystem::Update(i_elapsedSecondCount_sinceLastUpdate);
}

// Initialize / Clean Up
//----------------------

eae6320::cResult eae6320::cMyGame::Initialize()
{
	eae6320::Logging::OutputMessage("Initializing MyGame");
	auto result = Results::Success;

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

	ECS::ECSTestSystem ECSTest;
	ECSTest.Init();

	eae6320::ECS::RenderComponent::Init();
	eae6320::ECS::PhysicsSystem::Init();

	//eae6320::ECS::PhysicsSystem::CreatePhysicsComponent((*entity2).m_rigidBody, entity2);

	//eae6320::ECS::RenderComponent::CreateRenderComponent(geometryArray[3], effectArray[0], (*entity2).m_rigidBody, entity2);
	ECSTest.CreateTestComponent("test", entity);
	ECSTest.CreateTestComponent("asdfasdfasdf", entity2);

	ECSTest.Update(1, 1);
	
	ECSTest.RemoveTestComponent(entity2);
	ECSTest.RemoveTestComponent(entity2);

	//ECSTest.RemoveTestComponent(entity);
	//entity.~SmartPointer();

	ECSTest.Update(1, 1);

	auto test = ECSTest.GetTestComponent(entity);

	auto test2 = ECSTest.GetTestComponent(entity2);

	gameObject.Init(geometryArray[2], effectArray[0]);
	gameObject2.Init(geometryArray[1], effectArray[1]);
	gameObject3.Init(geometryArray[3], effectArray[1]);
	camera.Init();
	camera.m_rigidBody.operator*().position = { 0,1,5 };

	eae6320::Logging::OutputMessage("Finished Initializing MyGame");
	return result;
}

eae6320::cResult eae6320::cMyGame::CleanUp()
{
	eae6320::Logging::OutputMessage("Cleaning Up MyGame");

	gameObject.CleanUp();
	gameObject2.CleanUp();
	gameObject3.CleanUp();
	camera.CleanUp();

	eae6320::ECS::RenderComponent::CleanUp();
	eae6320::ECS::PhysicsSystem::CleanUp();

	//geometry cleanup
	geometryArray[0]->DecrementReferenceCount();
	geometryArray[1]->DecrementReferenceCount();
	geometryArray[2]->DecrementReferenceCount();
	geometryArray[3]->DecrementReferenceCount();
	geometryArray[0] = nullptr;
	geometryArray[1] = nullptr;
	geometryArray[2] = nullptr;
	geometryArray[3] = nullptr;

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
	result = eae6320::Graphics::Geometry::MakeGeometry("data/Meshes/Ship.mesh", geometryArray[3]);
	return result;
}

eae6320::cResult eae6320::cMyGame::InitializeShadingData() {
	auto result = eae6320::Graphics::Effect::MakeEffect("data/Shaders/Vertex/standard.shader", "data/Shaders/Fragment/animatedColor.shader", effectArray[0]);
	if (!result)
		return result;

	result = eae6320::Graphics::Effect::MakeEffect("data/Shaders/Vertex/standard.shader", "data/Shaders/Fragment/standard.shader", effectArray[1]);

	return result;
}
