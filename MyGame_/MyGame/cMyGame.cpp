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
}

eae6320::cResult eae6320::cMyGame::SpawnMissile(eae6320::Math::sVector i_position, eae6320::Math::cQuaternion i_orientation, eae6320::Math::sVector i_velocity) {
	if (missileCount >= maxMissiles) {
		missleNeedsSetUp = false;
		missileCount = 0;
	}

	if (missleNeedsSetUp) {
		missileArray[missileCount].Init(geometryArray[3], effectArray[1]);
	}
	
	missileArray[missileCount].m_rigidBody.operator*().position = i_position;
	missileArray[missileCount].m_rigidBody.operator*().velocity = i_velocity;
	missileArray[missileCount].m_rigidBody.operator*().orientation = i_orientation;
	missileCount++;

	return Results::Success;
}

void eae6320::cMyGame::UpdateSimulationBasedOnInput() {
	Math::sVector forward = ship.m_rigidBody.operator*().orientation.CalculateForwardDirection();
	if (UserInput::IsKeyPressed(UserInput::KeyCodes::Space)) {
		spacepressed = true;
	}
	else {

		if (spacepressed == true) {
			SpawnMissile((ship.m_rigidBody.operator*().position + forward * 2), ship.m_rigidBody.operator*().orientation, Math::sVector(forward * 500));
		}
		spacepressed = false;
	}
	//testRocket.m_rigidBody.operator*().velocity += Math::sVector(forward * 5);

	if (UserInput::IsKeyPressed(UserInput::KeyCodes::Shift)) {
		shiftpressed = true;
	}
	else {
		shiftpressed = false;
	}

	//if (UserInput::IsKeyPressed(UserInput::KeyCodes::Up)) {
	//	gameObject.m_rigidBody.operator*().velocity += { 0.0f, 1.0f, 0.0f };
	//}
	//if (UserInput::IsKeyPressed(UserInput::KeyCodes::Down)) {
	//	gameObject.m_rigidBody.operator*().velocity += { 0.0f, -1.0f, 0.0f };
	//}
	//if (UserInput::IsKeyPressed(UserInput::KeyCodes::Right)) {
	//	gameObject.m_rigidBody.operator*().velocity += { 1.0f, 0.0f, 0.0f };
	//}
	//if (UserInput::IsKeyPressed(UserInput::KeyCodes::Left)) {
	//	gameObject.m_rigidBody.operator*().velocity += { -1.0f, 0.0f, 0.0f };
	//}

	if (UserInput::IsKeyPressed('Z')) {
		camera.m_rigidBody.operator*().velocity += { 0.0f, 1.0f, 0.0f };
	}
	if (UserInput::IsKeyPressed('X')) {
		camera.m_rigidBody.operator*().velocity += { 0.0f, -1.0f, 0.0f };
	}
	//if (UserInput::IsKeyPressed('D')) {
	//	gameObject3.m_rigidBody.operator*().velocity += { 10.0f, 0.0f, 0.0f };
	//}
	//if (UserInput::IsKeyPressed('A')) {
	//	gameObject3.m_rigidBody.operator*().velocity += { -10.0f, 0.0f, 0.0f };
	//}
	if (UserInput::IsKeyPressed('S')) {
		//gameObject3.m_rigidBody.operator*().velocity += { 0.0f, 0.0f, 10.0f };
		ship.m_rigidBody.operator*().velocity -= forward*10;
	}
	if (UserInput::IsKeyPressed('W')) {
		//gameObject3.m_rigidBody.operator*().velocity += { 0.0f, 0.0f, -10.0f };
		ship.m_rigidBody.operator*().velocity += forward * 10;
	}

	if (UserInput::IsKeyPressed('A')) {
		ship.m_rigidBody.operator*().angularSpeed = 5.0f;
	}
	else if (UserInput::IsKeyPressed('D')) {
		ship.m_rigidBody.operator*().angularSpeed = -5.0f;
	}
	else {
		ship.m_rigidBody.operator*().angularSpeed = 0.0f;
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

	//ECS::ECSTestSystem ECSTest;
	//ECSTest.Init();

	eae6320::ECS::RenderComponent::Init();
	eae6320::ECS::PhysicsSystem::Init();

	//ECSTest.CreateTestComponent("test", entity);
	//ECSTest.CreateTestComponent("asdfasdfasdf", entity2);
	//
	//ECSTest.Update(1, 1);
	//
	//ECSTest.RemoveTestComponent(entity2);
	//ECSTest.RemoveTestComponent(entity2);

	//ECSTest.RemoveTestComponent(entity);
	//entity.~SmartPointer();

	//ECSTest.Update(1, 1);

	//auto test = ECSTest.GetTestComponent(entity);

	//auto test2 = ECSTest.GetTestComponent(entity2);

	gameObject.Init(geometryArray[2], effectArray[0]);
	spaceBackground.Init(geometryArray[1], effectArray[2]);
	ship.Init(geometryArray[4], effectArray[1]);
	camera.Init();
	camera.m_rigidBody.operator*().position = { 0, 150, 0 };
	camera.m_rigidBody.operator*().orientation = Math::cQuaternion(1,-1,0,0);

	eae6320::Logging::OutputMessage("Finished Initializing MyGame");
	return result;
}

eae6320::cResult eae6320::cMyGame::CleanUp()
{
	eae6320::Logging::OutputMessage("Cleaning Up MyGame");

	gameObject.CleanUp();
	spaceBackground.CleanUp();
	ship.CleanUp();
	testRocket.CleanUp();
	camera.CleanUp();

	eae6320::ECS::RenderComponent::CleanUp();
	eae6320::ECS::PhysicsSystem::CleanUp();

	//geometry cleanup
	geometryArray[0]->DecrementReferenceCount();
	geometryArray[1]->DecrementReferenceCount();
	geometryArray[2]->DecrementReferenceCount();
	geometryArray[3]->DecrementReferenceCount();
	geometryArray[4]->DecrementReferenceCount();
	geometryArray[5]->DecrementReferenceCount();
	geometryArray[6]->DecrementReferenceCount();
	geometryArray[7]->DecrementReferenceCount();
	geometryArray[0] = nullptr;
	geometryArray[1] = nullptr;
	geometryArray[2] = nullptr;
	geometryArray[3] = nullptr;
	geometryArray[4] = nullptr;
	geometryArray[5] = nullptr;
	geometryArray[6] = nullptr;
	geometryArray[7] = nullptr;

	//shader cleanup
	effectArray[0]->DecrementReferenceCount();
	effectArray[1]->DecrementReferenceCount();
	effectArray[2]->DecrementReferenceCount();
	effectArray[0] = nullptr;
	effectArray[1] = nullptr;
	effectArray[2] = nullptr;

	eae6320::Logging::OutputMessage("Finished Cleaning Up MyGame");
	return Results::Success;
}

eae6320::cResult eae6320::cMyGame::InitializeGeometry() {
	auto result = eae6320::Graphics::Geometry::MakeGeometry("data/Meshes/Sphere.mesh", geometryArray[0]);
	result = eae6320::Graphics::Geometry::MakeGeometry("data/Meshes/Plane.mesh", geometryArray[1]);
	result = eae6320::Graphics::Geometry::MakeGeometry("data/Meshes/ColoredCube.mesh", geometryArray[2]);
	result = eae6320::Graphics::Geometry::MakeGeometry("data/Meshes/Rocket.mesh", geometryArray[3]);
	result = eae6320::Graphics::Geometry::MakeGeometry("data/Meshes/Ship.mesh", geometryArray[4]);
	result = eae6320::Graphics::Geometry::MakeGeometry("data/Meshes/AS.mesh", geometryArray[5]);
	result = eae6320::Graphics::Geometry::MakeGeometry("data/Meshes/AM.mesh", geometryArray[6]);
	result = eae6320::Graphics::Geometry::MakeGeometry("data/Meshes/AL.mesh", geometryArray[7]);
	return result;
}

eae6320::cResult eae6320::cMyGame::InitializeShadingData() {
	auto result = eae6320::Graphics::Effect::MakeEffect("data/Shaders/Vertex/standard.shader", "data/Shaders/Fragment/animatedColor.shader", effectArray[0]);
	if (!result)
		return result;

	result = eae6320::Graphics::Effect::MakeEffect("data/Shaders/Vertex/standard.shader", "data/Shaders/Fragment/standard.shader", effectArray[1]);
	result = eae6320::Graphics::Effect::MakeEffect("data/Shaders/Vertex/standard.shader", "data/Shaders/Fragment/StarShader.shader", effectArray[2]);


	return result;
}
