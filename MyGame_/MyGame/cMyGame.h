/*
	This class is your specific game
*/

#ifndef EAE6320_CMYGAME_H
#define EAE6320_CMYGAME_H

// Includes
//=========

#include <Engine/Application/iApplication.h>
#include <Engine/Results/Results.h>
#include <Engine/Logging/Logging.h>
#include <Engine/Graphics/Graphics.h>
#include <Engine/Graphics/Effect.h>
#include <Engine/Graphics/Geometry.h>
#include <Engine/Application/GameObject.h>
#include <Engine/Application/CameraObject.h>
#include <Engine/EntityComponentSystem/ECSEntity.h>
#include <Engine/EntityComponentSystem/RenderComponent.h>
#include <Engine/EntityComponentSystem/PhysicsSystem.h>
#include <Engine/EntityComponentSystem/ECSCameraObject.h>
#include <Engine/EntityComponentSystem/ECSGameObject.h>

#if defined( EAE6320_PLATFORM_WINDOWS )
	#include "Resource Files/Resource.h"
#endif

// Class Declaration
//==================

namespace eae6320
{
	class cMyGame final : public Application::iApplication
	{
		// Inherited Implementation
		//=========================
		void SubmitDataToBeRendered(const float i_elapsedSecondCount_systemTime, const float i_elapsedSecondCount_sinceLastSimulationUpdate);
		void UpdateSimulationBasedOnTime(const float i_elapsedSecondCount_sinceLastUpdate);
	private:

		// Configuration
		//--------------

#if defined( EAE6320_PLATFORM_WINDOWS )
		// The main window's name will be displayed as its caption (the text that is displayed in the title bar).
		// You can make it anything that you want, but please keep the platform name and debug configuration at the end
		// so that it's easy to tell at a glance what kind of build is running.
		const char* GetMainWindowName() const final
		{
			return "Nate's EAE6320 Game"
				" -- "
#if defined( EAE6320_PLATFORM_D3D )
				"Direct3D"
#elif defined( EAE6320_PLATFORM_GL )
				"OpenGL"
#endif
#ifdef _DEBUG
				" -- Debug"
#endif
			;
		}
		// Window classes are almost always identified by name;
		// there is a unique "ATOM" associated with them,
		// but in practice Windows expects to use the class name as an identifier.
		// If you don't change the name below
		// your program could conceivably have problems if it were run at the same time on the same computer
		// as one of your classmate's.
		// You don't need to worry about this for our class,
		// but if you ever ship a real project using this code as a base you should set this to something unique
		// (a generated GUID would be fine since this string is never seen)
		const char* GetMainWindowClassName() const final { return "Nate's EAE6320 Main Window Class"; }
		// The following three icons are provided:
		//	* IDI_EAEGAMEPAD
		//	* IDI_EAEALIEN
		//	* IDI_VSDEFAULT_LARGE / IDI_VSDEFAULT_SMALL
		// If you want to try creating your own a convenient website that will help is: http://icoconvert.com/
		const WORD* GetLargeIconId() const final { static constexpr WORD iconId_large = IDI_EAEALIEN; return &iconId_large; }
		const WORD* GetSmallIconId() const final { static constexpr WORD iconId_small = IDI_EAEALIEN; return &iconId_small; }
#endif

		// Run
		//----

		void UpdateBasedOnInput() final;
		void UpdateSimulationBasedOnInput() final;

		// Initialize / Clean Up
		//----------------------

		cResult Initialize() final;
		cResult CleanUp() final;

		eae6320::cResult InitializeGeometry();
		eae6320::cResult InitializeShadingData();

		bool spacepressed = false;
		bool shiftpressed = false;

		// Geometry Data
		//--------------
		eae6320::Graphics::Geometry* geometryArray[30];
	
		// Shading Data
		//-------------
		eae6320::Graphics::Effect* effectArray[30];

		//eae6320::Application::GameObject m_gameObject;
		//eae6320::Application::GameObject m_gameObject2;
		//eae6320::Application::GameObject m_gameObject3;
		//eae6320::Application::CameraObject m_mainCamera;
		ECS::ECSCameraObject camera;
		eae6320::ECS::ECSGameObject* gameObject;
		eae6320::ECS::ECSGameObject* gameObject2;
		eae6320::ECS::ECSGameObject* gameObject3;
		SmartPointer<ECS::ECSEntity> entity = SmartPointer<ECS::ECSEntity>(new ECS::ECSEntity());
		SmartPointer<ECS::ECSEntity> entity2 = SmartPointer<ECS::ECSEntity>(new ECS::ECSEntity());
	};
}

// Result Definitions
//===================

namespace eae6320
{
	namespace Results
	{
		namespace Application
		{
			// You can add specific results for your game here:
			//	* The System should always be Application
			//	* The __LINE__ macro is used to make sure that every result has a unique ID.
			//		That means, however, that all results _must_ be defined in this single file
			//		or else you could have two different ones with equal IDs.
			//	* Note that you can define multiple Success codes.
			//		This can be used if the caller may want to know more about how a function succeeded.
			constexpr cResult ExampleResult( IsFailure, eSystem::Application, __LINE__, Severity::Default );
		}
	}
}

#endif	// EAE6320_CEXAMPLEGAME_H
