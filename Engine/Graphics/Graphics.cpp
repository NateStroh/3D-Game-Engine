#include "Graphics.h"

#include "cConstantBuffer.h"

#include "sContext.h"

#include <Engine/Asserts/Asserts.h>
#include <Engine/Concurrency/cEvent.h>
#include <Engine/Graphics/GraphicsHelper.h>
#include <Engine/UserOutput/UserOutput.h>
#include <Engine/Logging/Logging.h>


namespace
{
	// Constant buffer object
	eae6320::Graphics::cConstantBuffer s_constantBuffer_frame(eae6320::Graphics::ConstantBufferTypes::Frame);
	eae6320::Graphics::cConstantBuffer s_constantBuffer_drawCall(eae6320::Graphics::ConstantBufferTypes::DrawCall);

	// Submission Data
	//----------------
	const unsigned int MAX_GEOMETRY_EFFECT_PAIRS = 500;
	// This struct's data is populated at submission time;
	// it must cache whatever is necessary in order to render a frame
	struct sDataRequiredToRenderAFrame {
		eae6320::Graphics::ConstantBufferFormats::sFrame constantData_frame;
		eae6320::Graphics::sColor backgroundColor;
		eae6320::Graphics::sGeometryEffectPair geometryEffectPairList[MAX_GEOMETRY_EFFECT_PAIRS];
		unsigned int geometryEffectPairsToRender = 0;
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
			s_dataBeingSubmittedByApplicationThread->geometryEffectPairsToRender = 0;
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

	EAE6320_ASSERT(s_dataBeingRenderedByRenderThread);

	GraphicsHelper::ClearBackGroundBuffers(s_dataBeingRenderedByRenderThread->backgroundColor);

	// Update the frame constant buffer
	{
		// Copy the data from the system memory that the application owns to GPU memory
		auto& constantData_frame = s_dataBeingRenderedByRenderThread->constantData_frame;
		s_constantBuffer_frame.Update(&constantData_frame);
	}

	for (unsigned int i = 0; i < s_dataBeingRenderedByRenderThread->geometryEffectPairsToRender; i++) {
		s_constantBuffer_drawCall.Bind(static_cast<uint_fast8_t>(eShaderType::Vertex) | static_cast<uint_fast8_t>(eShaderType::Fragment));

		auto& constantData_drawCall = s_dataBeingRenderedByRenderThread->geometryEffectPairList[i].constantData_drawCall;
		s_constantBuffer_drawCall.Update(&constantData_drawCall);

		// Bind the shading data
		s_dataBeingRenderedByRenderThread->geometryEffectPairList[i].effect->Bind();
		
		// Draw the geometry
		s_dataBeingRenderedByRenderThread->geometryEffectPairList[i].geometry->Draw();
	}

	GraphicsHelper::Present();

	//clearing render frame before it's swapped back so the next frame will start clear
	for (unsigned int i = 0; i < s_dataBeingRenderedByRenderThread->geometryEffectPairsToRender; i++) {
		s_dataBeingRenderedByRenderThread->geometryEffectPairList[i].effect->DecrementReferenceCount();
		s_dataBeingRenderedByRenderThread->geometryEffectPairList[i].geometry->DecrementReferenceCount();
		s_dataBeingRenderedByRenderThread->geometryEffectPairList[i].effect = nullptr;
		s_dataBeingRenderedByRenderThread->geometryEffectPairList[i].geometry = nullptr;
	}
	s_dataBeingRenderedByRenderThread->geometryEffectPairsToRender = 0;
	//s_dataBeingRenderedByRenderThread->constantData_drawCall.g_transform_localToWorld = eae6320::Math::cMatrix_transformation();
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
			// In our class both vertex and fragment shaders use per-frame constant data
			s_constantBuffer_frame.Bind(static_cast<uint_fast8_t>(eShaderType::Vertex) | static_cast<uint_fast8_t>(eShaderType::Fragment));
		}
		else
		{
			EAE6320_ASSERTF(false, "Can't initialize Graphics without frame constant buffer");
			return result;
		}
	}
	// Initialize the platform-independent graphics objects
	{
		if (result = s_constantBuffer_drawCall.Initialize())
		{
			// There is only a single frame constant buffer that is reused
			// and so it can be bound at initialization time and never unbound
			s_constantBuffer_drawCall.Bind(
				// In our class both vertex and fragment shaders use per-frame constant data
				static_cast<uint_fast8_t>(eShaderType::Vertex) | static_cast<uint_fast8_t>(eShaderType::Fragment));
		}
		else
		{
			EAE6320_ASSERTF(false, "Can't initialize Graphics without drawCall constant buffer");
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

	return result;
}

eae6320::cResult eae6320::Graphics::CleanUp()
{
	auto result = Results::Success;

	//clearing any data that was waiting to be submitted
	for (unsigned int i = 0; i < s_dataBeingSubmittedByApplicationThread->geometryEffectPairsToRender; i++) {
		s_dataBeingSubmittedByApplicationThread->geometryEffectPairList[i].effect->DecrementReferenceCount();
		s_dataBeingSubmittedByApplicationThread->geometryEffectPairList[i].geometry->DecrementReferenceCount();
		s_dataBeingSubmittedByApplicationThread->geometryEffectPairList[i].effect = nullptr;
		s_dataBeingSubmittedByApplicationThread->geometryEffectPairList[i].geometry = nullptr;
	}
	s_dataBeingSubmittedByApplicationThread->geometryEffectPairsToRender = 0;

	GraphicsHelper::CleanUp();

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
		const auto result_constantBuffer_drawCall = s_constantBuffer_drawCall.CleanUp();
		if (!result_constantBuffer_drawCall)
		{
			EAE6320_ASSERT(false);
			if (result)
			{
				result = result_constantBuffer_drawCall;
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

void eae6320::Graphics::AddGeometryEffectPair(Geometry* i_geometry, Math::cMatrix_transformation i_transform, Effect* i_effect) {
#ifdef _DEBUG
	EAE6320_ASSERT(s_dataBeingSubmittedByApplicationThread->geometryEffectPairsToRender < MAX_GEOMETRY_EFFECT_PAIRS);
#endif
	if (s_dataBeingSubmittedByApplicationThread->geometryEffectPairsToRender < MAX_GEOMETRY_EFFECT_PAIRS) {
		i_geometry->IncrementReferenceCount();
		i_effect->IncrementReferenceCount();
		s_dataBeingSubmittedByApplicationThread->geometryEffectPairList[s_dataBeingSubmittedByApplicationThread->geometryEffectPairsToRender].geometry = i_geometry;
		s_dataBeingSubmittedByApplicationThread->geometryEffectPairList[s_dataBeingSubmittedByApplicationThread->geometryEffectPairsToRender].constantData_drawCall.g_transform_localToWorld = i_transform;
		s_dataBeingSubmittedByApplicationThread->geometryEffectPairList[s_dataBeingSubmittedByApplicationThread->geometryEffectPairsToRender].effect = i_effect;
		s_dataBeingSubmittedByApplicationThread->geometryEffectPairsToRender++;

	}
	else {
		Logging::OutputError("Went over the mesh/effect limit - offending item was not submitted to be rendered\n");
	}
}

