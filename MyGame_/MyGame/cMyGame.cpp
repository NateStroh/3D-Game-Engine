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
	
	eae6320::Logging::OutputMessage("Finished Initializing MyGame");
	return Results::Success;
}

eae6320::cResult eae6320::cMyGame::CleanUp()
{
	eae6320::Logging::OutputMessage("Cleaning Up MyGame");

	eae6320::Logging::OutputMessage("Finished Cleaning Up MyGame");
	return Results::Success;
}
