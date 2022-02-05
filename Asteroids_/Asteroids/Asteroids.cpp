 // Includes
//=========

#include "Asteroids.h"

#include <Engine/Asserts/Asserts.h>
#include <Engine/UserInput/UserInput.h>
#include <Engine/Math/cMatrix_transformation.h>
#include <Engine/EntityComponentSystem/ECSTestSystem.h>
#include <Engine/EntityComponentSystem/SmartPointer.h>
#include <Engine/Time/Time.h>

#include <stdlib.h>
#include <time.h>

// Inherited Implementation
//=========================

// Run
//----

void eae6320::Asteroids::SubmitDataToBeRendered(const float i_elapsedSecondCount_systemTime, const float i_elapsedSecondCount_sinceLastSimulationUpdate) {
	Graphics::SetBackGroundColor(1.0f, 0.0f, 1.0f, 1.0f);

	//if(shiftpressed){
	//	eae6320::ECS::RenderComponent::ChangeGeometry(geometryArray[0], effectArray[1], gameObject.m_pointer);
	//}
	//else {
	//	eae6320::ECS::RenderComponent::ChangeGeometry(geometryArray[2], effectArray[0], gameObject.m_pointer);
	//}
	
	camera.SubmitToBeRendered(i_elapsedSecondCount_systemTime, i_elapsedSecondCount_sinceLastSimulationUpdate);

	eae6320::ECS::RenderComponent::Update(i_elapsedSecondCount_systemTime, i_elapsedSecondCount_sinceLastSimulationUpdate);
}

void eae6320::Asteroids::UpdateBasedOnInput()
{
	// Is the user pressing the ESC key?
	if ( UserInput::IsKeyPressed( UserInput::KeyCodes::Escape ) )
	{
		// Exit the application
		const auto result = Exit( EXIT_SUCCESS );
		EAE6320_ASSERT( result );
	}
}

eae6320::cResult eae6320::Asteroids::SpawnMissile(eae6320::Math::sVector i_position, eae6320::Math::cQuaternion i_orientation, eae6320::Math::sVector i_velocity) {
	if (missileCount >= maxMissiles) {
		missleNeedsSetUp = false;
		missileCount = 0;
	}

	if (missleNeedsSetUp) {
		missileArray[missileCount].Init(geometryArray[3], effectArray[1], {1, 1, 1}, true, 2, 0);
		missileArray[missileCount].m_collider->ListenToCollision(std::bind(&eae6320::Asteroids::ResolveCollision, this, std::placeholders::_1));
	}
	
	missileArray[missileCount].m_rigidBody.operator*().position = i_position;
	missileArray[missileCount].m_rigidBody.operator*().velocity = i_velocity;
	//missileArray[missileCount].m_rigidBody.operator*().orientation = i_orientation;
	missileCount++;

	return Results::Success;
}

eae6320::cResult eae6320::Asteroids::SpawnAsteroid()
{
	srand(static_cast<unsigned int>((Time::GetCurrentSystemTimeTickCount())));

	if (asteroidCount >= maxAsteroids) {
		asteroidsNeedsSetUp = false;
		asteroidCount = 0;
	}

	int asteroidType = rand() % 3;

	if (asteroidsNeedsSetUp) {
		switch (asteroidType) {
		case 0:
			asteroidArray[asteroidCount].Init(geometryArray[5], effectArray[1], {10,1,10}, true, 1, 0, 30);
			asteroidArray[asteroidCount].m_collider->ListenToCollision(std::bind(&eae6320::Asteroids::ResolveCollision, this, std::placeholders::_1));
			break;
		case 1:
			asteroidArray[asteroidCount].Init(geometryArray[6], effectArray[1], { 20,1,20 }, true, 1, 0, 30);
			asteroidArray[asteroidCount].m_collider->ListenToCollision(std::bind(&eae6320::Asteroids::ResolveCollision, this, std::placeholders::_1));
			break;
		case 2:
			asteroidArray[asteroidCount].Init(geometryArray[7], effectArray[1], { 30,1,30 }, true, 1, 0, 30);
			asteroidArray[asteroidCount].m_collider->ListenToCollision(std::bind(&eae6320::Asteroids::ResolveCollision, this, std::placeholders::_1));
			break;
		default:
			asteroidArray[asteroidCount].Init(geometryArray[5], effectArray[1], { 10,1,10 }, true, 1, 0, 30);
			asteroidArray[asteroidCount].m_collider->ListenToCollision(std::bind(&eae6320::Asteroids::ResolveCollision, this, std::placeholders::_1));
			break;
		}
	}
	int asteroidLocation = rand() % 8;


	float xVelocity;
	float zVelocity;

	switch (asteroidLocation) {
	//bottom left
	case 0:
		xVelocity = static_cast<float>(rand() % 200 + 100);
		zVelocity = static_cast<float>(rand() % 200 - 300);

		asteroidArray[asteroidCount].m_rigidBody.operator*().position = { -150, 0, 150 };
		asteroidArray[asteroidCount].m_rigidBody.operator*().velocity = { xVelocity, 0, zVelocity };

		break;
	//left
	case 1:
		xVelocity = static_cast<float>(rand() % 200 + 100);
		zVelocity = static_cast<float>(rand() % 400 - 200);

		asteroidArray[asteroidCount].m_rigidBody.operator*().position = { -150, 0, 0 };
		asteroidArray[asteroidCount].m_rigidBody.operator*().velocity = { xVelocity, 0, zVelocity };

		break;
	//top left
	case 2:
		xVelocity = static_cast<float>(rand() % 200 + 100);
		zVelocity = static_cast<float>(rand() % 200 + 100);

		asteroidArray[asteroidCount].m_rigidBody.operator*().position = { -150, 0, -150 };
		asteroidArray[asteroidCount].m_rigidBody.operator*().velocity = { xVelocity, 0, zVelocity };
		break;
	//top
	case 3:
		xVelocity = static_cast<float>(rand() % 400 - 200);
		zVelocity = static_cast<float>(rand() % 200 + 100);

		asteroidArray[asteroidCount].m_rigidBody.operator*().position = { 0, 0, -150 };
		asteroidArray[asteroidCount].m_rigidBody.operator*().velocity = { xVelocity, 0, zVelocity };

		break;
	//top right
	case 4:
		xVelocity = static_cast<float>(rand() % 200 - 300);
		zVelocity = static_cast<float>(rand() % 200 + 100);

		asteroidArray[asteroidCount].m_rigidBody.operator*().position = { 150, 0, -150 };
		asteroidArray[asteroidCount].m_rigidBody.operator*().velocity = { xVelocity, 0, zVelocity };

		break;
	//right
	case 5:
		xVelocity = static_cast<float>(rand() % 200 - 300);
		zVelocity = static_cast<float>(rand() % 400 - 200);

		asteroidArray[asteroidCount].m_rigidBody.operator*().position = { 150, 0, 0 };
		asteroidArray[asteroidCount].m_rigidBody.operator*().velocity = { xVelocity, 0, zVelocity };

		break;
	//bottom right
	case 6:
		xVelocity = static_cast<float>(rand() % 200 - 300);
		zVelocity = static_cast<float>(rand() % 200 - 300);

		asteroidArray[asteroidCount].m_rigidBody.operator*().position = { 150, 0, 150 };
		asteroidArray[asteroidCount].m_rigidBody.operator*().velocity = { xVelocity, 0, zVelocity };

		break;
	//bottom
	case 7:
		xVelocity = static_cast<float>(rand() % 400 - 200);
		zVelocity = static_cast<float>(rand() % 200 - 300);

		asteroidArray[asteroidCount].m_rigidBody.operator*().position = { 0, 0, 150 };
		asteroidArray[asteroidCount].m_rigidBody.operator*().velocity = { xVelocity, 0, zVelocity };

		break;
	default:
		xVelocity = static_cast<float>(rand() % 200 + 100);
		zVelocity = static_cast<float>(rand() % 200 + 100);

		asteroidArray[asteroidCount].m_rigidBody.operator*().position = { -150, 0, 150 };
		asteroidArray[asteroidCount].m_rigidBody.operator*().velocity = { xVelocity, 0, zVelocity };

		break;
	
	}

	asteroidCount++;

	return Results::Success;
}

void eae6320::Asteroids::UpdateSimulationBasedOnInput() {
	Math::sVector forward = ship.m_rigidBody.operator*().orientation.CalculateForwardDirection();
	if (UserInput::IsKeyPressed(UserInput::KeyCodes::Space)) {
		spacepressed = true;
	}
	else {

		if (spacepressed == true) {
			SpawnMissile((ship.m_rigidBody.operator*().position + forward * 10), ship.m_rigidBody.operator*().orientation, Math::sVector(forward * 300));
		}
		spacepressed = false;
	}

	if (UserInput::IsKeyPressed(UserInput::KeyCodes::Shift)) {
		shiftpressed = true;
	}
	else {
		//if (shiftpressed == true) {
		//	SpawnAsteroid();
		//}
		shiftpressed = false;
	}

	if (UserInput::IsKeyPressed('Z')) {
		camera.m_rigidBody.operator*().velocity += { 0.0f, 1.0f, 0.0f };
	}
	if (UserInput::IsKeyPressed('X')) {
		camera.m_rigidBody.operator*().velocity += { 0.0f, -1.0f, 0.0f };
	}
	if (UserInput::IsKeyPressed('S')) {
		ship.m_rigidBody.operator*().velocity -= forward*10;
	}
	if (UserInput::IsKeyPressed('W')) {
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

bool InRange(double i_low, double i_high, double i_number) {
	return (i_number <= i_high && i_number >= i_low);
}

void eae6320::Asteroids::UpdateSimulationBasedOnTime(const float i_elapsedSecondCount_sinceLastUpdate) {

	if (ship.m_rigidBody.operator*().position.z >= 110) {
		ship.m_rigidBody.operator*().position.z = -110;
	}
	else if (ship.m_rigidBody.operator*().position.z <= -110) {
		ship.m_rigidBody.operator*().position.z = 110;
	}
	else if (ship.m_rigidBody.operator*().position.x >= 110) {
		ship.m_rigidBody.operator*().position.x = -110;
	}
	else if (ship.m_rigidBody.operator*().position.x <= -110) {
		ship.m_rigidBody.operator*().position.x = 110;
	}

	auto currTime = (Time::ConvertTicksToSeconds(Time::GetCurrentSystemTimeTickCount()));
	if (InRange(0,0.07,fmod(currTime, 1.0))) {
		SpawnAsteroid();
	}

	eae6320::ECS::PhysicsSystem::Update(i_elapsedSecondCount_sinceLastUpdate);

	Collision::UpdateCollisions(i_elapsedSecondCount_sinceLastUpdate);
}

// Initialize / Clean Up
//----------------------

eae6320::cResult eae6320::Asteroids::Initialize()
{

	Time::Initialize();

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

	result = Collision::Initialize();

	eae6320::ECS::RenderComponent::Init();
	eae6320::ECS::PhysicsSystem::Init();

	LoseText.Init(geometryArray[8], effectArray[1]);
	LoseText.m_rigidBody.operator*().position = { 0,-100,0 };
	
	spaceBackground.Init(geometryArray[1], effectArray[2]);

	ship.Init(geometryArray[4], effectArray[1], {1,1,2}, true, 0, 0, 60);
	ship.m_collider->ListenToCollision(std::bind(&eae6320::Asteroids::ResolveCollision, this, std::placeholders::_1));

	camera.Init();
	camera.m_rigidBody.operator*().position = { 0, 250, 0 };
	camera.m_rigidBody.operator*().orientation = Math::cQuaternion(1,-1,0,0);

	//collTest.Init(geometryArray[5], effectArray[0], { 10,1,10 }, false);
	//collTest.m_rigidBody.operator*().position = { 0,0, 50 };
	//
	//collTest1.Init(geometryArray[2], effectArray[0], { 1,1,1 }, false);
	//collTest1.m_rigidBody.operator*().position = { 0,0, -50 };

	eae6320::Logging::OutputMessage("Finished Initializing MyGame");
	return result;
}

eae6320::cResult eae6320::Asteroids::CleanUp()
{
	eae6320::Logging::OutputMessage("Cleaning Up MyGame");

	LoseText.CleanUp();
	spaceBackground.CleanUp();
	ship.CleanUp();
	camera.CleanUp();

	for (uint16_t i = 0; i < maxAsteroids; i++) {
		asteroidArray[i].CleanUp();
	}

	for (uint16_t i = 0; i < maxMissiles; i++) {
		missileArray[i].CleanUp();
	}

	eae6320::ECS::RenderComponent::CleanUp();
	eae6320::ECS::PhysicsSystem::CleanUp();

	Collision::CleanUp();

	//geometry cleanup
	geometryArray[0]->DecrementReferenceCount();
	geometryArray[1]->DecrementReferenceCount();
	geometryArray[2]->DecrementReferenceCount();
	geometryArray[3]->DecrementReferenceCount();
	geometryArray[4]->DecrementReferenceCount();
	geometryArray[5]->DecrementReferenceCount();
	geometryArray[6]->DecrementReferenceCount();
	geometryArray[7]->DecrementReferenceCount();
	geometryArray[8]->DecrementReferenceCount();
	geometryArray[0] = nullptr;
	geometryArray[1] = nullptr;
	geometryArray[2] = nullptr;
	geometryArray[3] = nullptr;
	geometryArray[4] = nullptr;
	geometryArray[5] = nullptr;
	geometryArray[6] = nullptr;
	geometryArray[7] = nullptr;
	geometryArray[8] = nullptr;

	//shader cleanup
	effectArray[0]->DecrementReferenceCount();
	effectArray[1]->DecrementReferenceCount();
	effectArray[2]->DecrementReferenceCount();
	effectArray[0] = nullptr;
	effectArray[1] = nullptr;
	effectArray[2] = nullptr;

	Time::CleanUp();

	eae6320::Logging::OutputMessage("Finished Cleaning Up MyGame");
	return Results::Success;
}

eae6320::cResult eae6320::Asteroids::InitializeGeometry() {
	auto result = eae6320::Graphics::Geometry::MakeGeometry("data/Meshes/Sphere.mesh", geometryArray[0]);
	result = eae6320::Graphics::Geometry::MakeGeometry("data/Meshes/Plane.mesh", geometryArray[1]);
	result = eae6320::Graphics::Geometry::MakeGeometry("data/Meshes/ColoredCube.mesh", geometryArray[2]);
	result = eae6320::Graphics::Geometry::MakeGeometry("data/Meshes/Rocket.mesh", geometryArray[3]);
	result = eae6320::Graphics::Geometry::MakeGeometry("data/Meshes/Ship.mesh", geometryArray[4]);
	result = eae6320::Graphics::Geometry::MakeGeometry("data/Meshes/AS.mesh", geometryArray[5]);
	result = eae6320::Graphics::Geometry::MakeGeometry("data/Meshes/AM.mesh", geometryArray[6]);
	result = eae6320::Graphics::Geometry::MakeGeometry("data/Meshes/AL.mesh", geometryArray[7]);
	result = eae6320::Graphics::Geometry::MakeGeometry("data/Meshes/LoseText.mesh", geometryArray[8]);
	return result;
}

eae6320::cResult eae6320::Asteroids::InitializeShadingData() {
	auto result = eae6320::Graphics::Effect::MakeEffect("data/Shaders/Vertex/standard.shader", "data/Shaders/Fragment/animatedColor.shader", effectArray[0]);
	if (!result)
		return result;

	result = eae6320::Graphics::Effect::MakeEffect("data/Shaders/Vertex/standard.shader", "data/Shaders/Fragment/standard.shader", effectArray[1]);
	result = eae6320::Graphics::Effect::MakeEffect("data/Shaders/Vertex/standard.shader", "data/Shaders/Fragment/StarShader.shader", effectArray[2]);


	return result;
}

void eae6320::Asteroids::ResolveCollision(eae6320::Collision::sCollision coll)
{
	if ((coll.colliderA->CollisionType == 1 && coll.colliderB->CollisionType == 1) || (coll.colliderA->CollisionType == 2 && coll.colliderB->CollisionType == 2))
		return;

 	if (coll.colliderA->CollisionType == 0 && (coll.colliderB->CollisionType == 1 || coll.colliderB->CollisionType == 2)) {
		LoseText.m_rigidBody.operator*().position = { 0,50,0 };
		SetSimulationRate(0);
	}
	else if((coll.colliderA->CollisionType == 1 && coll.colliderB->CollisionType == 0) || (coll.colliderA->CollisionType == 2 && coll.colliderB->CollisionType == 0)) {
		LoseText.m_rigidBody.operator*().position = { 0,50,0 };
		SetSimulationRate(0);
	}

	if ((coll.colliderA->CollisionType == 1 && coll.colliderB->CollisionType == 2) || (coll.colliderA->CollisionType == 2 && coll.colliderB->CollisionType == 1)) {
		coll.colliderA->rigidbody->position = { 0,500,0 };
		coll.colliderA->rigidbody->velocity = { 0,0,0 };
		coll.colliderB->rigidbody->position = { 0,-500,0 };
		coll.colliderB->rigidbody->velocity = { 0,0,0 };
	}
}