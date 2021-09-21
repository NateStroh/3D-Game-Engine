#include "Graphics.h"

#include "cConstantBuffer.h"
#include "ConstantBufferFormats.h"
#include "cRenderState.h"
#include "cShader.h"
#include "cVertexFormat.h"
#include "sContext.h"
#include "VertexFormats.h"

#include <Engine/Asserts/Asserts.h>
#include <Engine/Concurrency/cEvent.h>
#include <Engine/Graphics/Geometry.h>
#include <Engine/Graphics/GraphicsHelper.h>
#include <Engine/Graphics/Effect.h>
#include <Engine/Logging/Logging.h>
#include <Engine/Platform/Platform.h>
#include <Engine/ScopeGuard/cScopeGuard.h>
#include <Engine/Time/Time.h>
#include <Engine/UserOutput/UserOutput.h>
#include <utility>

namespace
{
	// Constant buffer object
	eae6320::Graphics::cConstantBuffer s_constantBuffer_frame(eae6320::Graphics::ConstantBufferTypes::Frame);

	// Submission Data
	//----------------

	// This struct's data is populated at submission time;
	// it must cache whatever is necessary in order to render a frame
	struct sDataRequiredToRenderAFrame
	{
		eae6320::Graphics::ConstantBufferFormats::sFrame constantData_frame;
		eae6320::Graphics::sColor backgroundColor;
	};
	// In our class there will be two copies of the data required to render a frame:
	//	* One of them will be in the process of being populated by the data currently being submitted by the application loop thread
	//	* One of them will be fully populated and in the process of being rendered from in the render thread
	// (In other words, one is being produced while the other is being consumed)
	sDataRequiredToRenderAFrame s_dataRequiredToRenderAFrame[2];
	auto* s_dataBeingSubmittedByApplicationThread = &s_dataRequiredToRenderAFrame[0];
	auto* s_dataBeingRenderedByRenderThread = &s_dataRequiredToRenderAFrame[1];
	// The following two events work together to make sure that
	// the main/render thread and the application loop thread can work in parallel but stay in sync:
	// This event is signaled by the application loop thread when it has finished submitting render data for a frame
	// (the main/render thread waits for the signal)
	eae6320::Concurrency::cEvent s_whenAllDataHasBeenSubmittedFromApplicationThread;
	// This event is signaled by the main/render thread when it has swapped render data pointers.
	// This means that the renderer is now working with all the submitted data it needs to render the next frame,
	// and the application loop thread can start submitting data for the following frame
	// (the application loop thread waits for the signal)
	eae6320::Concurrency::cEvent s_whenDataForANewFrameCanBeSubmittedFromApplicationThread;

	// Geometry Data
	//--------------

	eae6320::Graphics::Geometry testGeometry;
	eae6320::Graphics::Geometry testGeometry2;

	// Shading Data
	//-------------

	eae6320::Graphics::Effect testEffect;
	eae6320::Graphics::Effect testEffect2;
}

// Helper Declarations
//====================

namespace
{
	eae6320::cResult InitializeGeometry();
	eae6320::cResult InitializeShadingData();
}

// Interface
//==========

// Submission
//-----------

void eae6320::Graphics::SubmitElapsedTime(const float i_elapsedSecondCount_systemTime, const float i_elapsedSecondCount_simulationTime)
{
	EAE6320_ASSERT(s_dataBeingSubmittedByApplicationThread);
	auto& constantData_frame = s_dataBeingSubmittedByApplicationThread->constantData_frame;
	constantData_frame.g_elapsedSecondCount_systemTime = i_elapsedSecondCount_systemTime;
	constantData_frame.g_elapsedSecondCount_simulationTime = i_elapsedSecondCount_simulationTime;
}

eae6320::cResult eae6320::Graphics::WaitUntilDataForANewFrameCanBeSubmitted(const unsigned int i_timeToWait_inMilliseconds)
{
	return Concurrency::WaitForEvent(s_whenDataForANewFrameCanBeSubmittedFromApplicationThread, i_timeToWait_inMilliseconds);
}

eae6320::cResult eae6320::Graphics::SignalThatAllDataForAFrameHasBeenSubmitted()
{
	return s_whenAllDataHasBeenSubmittedFromApplicationThread.Signal();
}

// Render
//-------

void eae6320::Graphics::RenderFrame()
{
	// Wait for the application loop to submit data to be rendered
	{
		if (Concurrency::WaitForEvent(s_whenAllDataHasBeenSubmittedFromApplicationThread))
		{
			// Switch the render data pointers so that
			// the data that the application just submitted becomes the data that will now be rendered
			std::swap(s_dataBeingSubmittedByApplicationThread, s_dataBeingRenderedByRenderThread);
			// Once the pointers have been swapped the application loop can submit new data
			if (!s_whenDataForANewFrameCanBeSubmittedFromApplicationThread.Signal())
			{
				EAE6320_ASSERTF(false, "Couldn't signal that new graphics data can be submitted");
				Logging::OutputError("Failed to signal that new render data can be submitted");
				UserOutput::Print("The renderer failed to signal to the application that new graphics data can be submitted."
					" The application is probably in a bad state and should be exited");
				return;
			}
		}
		else
		{
			EAE6320_ASSERTF(false, "Waiting for the graphics data to be submitted failed");
			Logging::OutputError("Waiting for the application loop to submit data to be rendered failed");
			UserOutput::Print("The renderer failed to wait for the application to submit data to be rendered."
				" The application is probably in a bad state and should be exited");
			return;
		}
	}

	GraphicsHelper::ClearBackGroundBuffers(s_dataBeingRenderedByRenderThread->backgroundColor);

	EAE6320_ASSERT(s_dataBeingRenderedByRenderThread);

	// Update the frame constant buffer
	{
		// Copy the data from the system memory that the application owns to GPU memory
		auto& constantData_frame = s_dataBeingRenderedByRenderThread->constantData_frame;
		s_constantBuffer_frame.Update(&constantData_frame);
	}

	// Bind the shading data
	{
		testEffect.Bind();
	}
	// Draw the geometry
	{
		testGeometry.Draw();
	}
	// Bind the shading data
	{
		testEffect2.Bind();
	}
	// Draw the geometry
	{
		testGeometry2.Draw();
	}

	GraphicsHelper::Present();

}

eae6320::cResult eae6320::Graphics::Initialize(const sInitializationParameters& i_initializationParameters)
{
	auto result = Results::Success;

	// Initialize the platform-specific context
	if (!(result = sContext::g_context.Initialize(i_initializationParameters)))
	{
		EAE6320_ASSERTF(false, "Can't initialize Graphics without context");
		return result;
	}
	// Initialize the platform-independent graphics objects
	{
		if (result = s_constantBuffer_frame.Initialize())
		{
			// There is only a single frame constant buffer that is reused
			// and so it can be bound at initialization time and never unbound
			s_constantBuffer_frame.Bind(
				// In our class both vertex and fragment shaders use per-frame constant data
				static_cast<uint_fast8_t>(eShaderType::Vertex) | static_cast<uint_fast8_t>(eShaderType::Fragment));
		}
		else
		{
			EAE6320_ASSERTF(false, "Can't initialize Graphics without frame constant buffer");
			return result;
		}
	}
	// Initialize the events
	{
		if (!(result = s_whenAllDataHasBeenSubmittedFromApplicationThread.Initialize(Concurrency::EventType::ResetAutomaticallyAfterBeingSignaled)))
		{
			EAE6320_ASSERTF(false, "Can't initialize Graphics without event for when data has been submitted from the application thread");
			return result;
		}
		if (!(result = s_whenDataForANewFrameCanBeSubmittedFromApplicationThread.Initialize(Concurrency::EventType::ResetAutomaticallyAfterBeingSignaled,
			Concurrency::EventState::Signaled)))
		{
			EAE6320_ASSERTF(false, "Can't initialize Graphics without event for when data can be submitted from the application thread");
			return result;
		}
	}
	
	GraphicsHelper::Initialize(i_initializationParameters);

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

	return result;
}

eae6320::cResult eae6320::Graphics::CleanUp()
{
	auto result = Results::Success;

	GraphicsHelper::CleanUp();

	//geometry cleanup
	testGeometry.CleanUp();
	testGeometry2.CleanUp();

	//shader cleanup
	testEffect.CleanUp();
	testEffect2.CleanUp();

	{
		const auto result_constantBuffer_frame = s_constantBuffer_frame.CleanUp();
		if (!result_constantBuffer_frame)
		{
			EAE6320_ASSERT(false);
			if (result)
			{
				result = result_constantBuffer_frame;
			}
		}
	}

	{
		const auto result_context = sContext::g_context.CleanUp();
		if (!result_context)
		{
			EAE6320_ASSERT(false);
			if (result)
			{
				result = result_context;
			}
		}
	}

	return result;
}

void eae6320::Graphics::SetBackGroundColor(float i_redVal, float i_greenVal, float i_blueVal, float i_opacity) {
	s_dataBeingSubmittedByApplicationThread->backgroundColor.Red = i_redVal;
	s_dataBeingSubmittedByApplicationThread->backgroundColor.Green = i_greenVal; 
	s_dataBeingSubmittedByApplicationThread->backgroundColor.Blue = i_blueVal; 
	s_dataBeingSubmittedByApplicationThread->backgroundColor.Opacity = i_opacity;
}

void eae6320::Graphics::SetBackGroundColor(sColor i_color) {
	s_dataBeingSubmittedByApplicationThread->backgroundColor = i_color;
}

// Helper Definitions
//===================

namespace
{
	eae6320::cResult InitializeGeometry()
	{

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
		uint16_t indexData[6] = {0, 1, 2, 0, 2, 3};
		//{0, 3, 2, 0, 2, 1};

		auto result = testGeometry.Initialize(geometryVertexData, 4, indexData, 6);
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
		uint16_t indexData2[9] = {0, 1, 3, 1, 2, 3, 0, 3, 4};
		//{0, 3, 1, 1, 3, 2, 0, 4, 3};

		result = testGeometry2.Initialize(geometryVertexData2, 5, indexData2, 9);

		return result;
	}

	eae6320::cResult InitializeShadingData()
	{
		auto result = testEffect.Initialize("data/Shaders/Vertex/standard.shader", "data/Shaders/Fragment/animatedColor.shader");
		if (!result)
			return result;

		result = testEffect2.Initialize("data/Shaders/Vertex/standard.shader", "data/Shaders/Fragment/standard.shader");

		return result;
	}
}