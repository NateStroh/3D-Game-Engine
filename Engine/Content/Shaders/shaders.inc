/*
	This file should be #included by all shaders
*/

// Version Information
//====================

#if defined( EAE6320_PLATFORM_GL )

	// GLSL shaders require the version to be #defined before anything else in the shader
	#version 420

#endif

// Constant Buffers
//=================

#if defined( EAE6320_PLATFORM_D3D )
	#define DeclareConstantBuffer( i_name, i_id ) cbuffer i_name : register( b##i_id )
	#define MULT(i_local, i_localToWorld) mul(i_local, i_localToWorld)
	#define OUTPUT o_vertexPosition_projected
	#define mat4 float4x4
	#define vec2 float2
	#define vec3 float3
	#define vec4 float4
#elif defined( EAE6320_PLATFORM_GL )
	#define DeclareConstantBuffer( i_name, i_id ) layout( std140, binding = i_id ) uniform i_name
	#define MULT(i_local, i_localToWorld) i_local * i_localToWorld
	#define OUTPUT gl_Position
	#define float4x4 mat4
	#define float2 vec2
	#define float3 vec3
	#define float4 vec4
	layout(location = 0) in vec3 i_vertexPosition_local;
	layout(location = 0) out vec4 o_color;
#endif
