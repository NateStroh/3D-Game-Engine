/*
	This is the standard fragment shader

	A fragment shader is responsible for telling the GPU what color a specific fragment should be
*/

#include <Shaders/shaders.inc>

#if defined( EAE6320_PLATFORM_D3D )
	#define mat4 float4x4
	#define vec2 float2
	#define vec4 float4
#elif defined( EAE6320_PLATFORM_GL )
	#define float4x4 mat4
	#define float2 vec2
	#define float4 vec4
	out vec4 o_color;
#endif

// Constant Buffers
//=================

DeclareConstantBuffer(g_constantBuffer_frame, 0)
{
	float4x4 g_transform_worldToCamera;
	float4x4 g_transform_cameraToProjected;

	float g_elapsedSecondCount_systemTime;
	float g_elapsedSecondCount_simulationTime;
	// For float4 alignment
	float2 g_padding;
};

// Entry Point
//============
void main(
#if defined( EAE6320_PLATFORM_D3D )
	// Input
	//======

	in const float4 i_fragmentPosition : SV_POSITION,

	// Output
	//=======

	// Whatever color value is output from the fragment shader
	// will determine the color of the corresponding pixel on the screen
	out float4 o_color : SV_TARGET
#endif
) {
	// Output solid white
	o_color = float4(
		// RGB (color)
		1.0, 1.0, 1.0,
		// Alpha (opacity)
		1.0);
}
