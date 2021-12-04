/*
	This is the standard fragment shader

	A fragment shader is responsible for telling the GPU what color a specific fragment should be
*/

#include <Shaders/shaders.inc>

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

#if defined( EAE6320_PLATFORM_GL )
	layout(location = 1) in float4 vertexColor;
	//layout( location = 2 ) in vec3 i_position;
#endif


float random (vec2 st) {
    return frac(sin(dot(st.xy, vec2(12.9898,78.233)))*43758.5453123)*100.0;
}

// Entry Point
//============
void main(
#if defined( EAE6320_PLATFORM_D3D )
	// Input
	//======

	in const float4 i_fragmentPosition : SV_POSITION,
	in const float4 vertexColor : COLOR,
	// Output
	//=======

	// Whatever color value is output from the fragment shader
	// will determine the color of the corresponding pixel on the screen
	out float4 o_color : SV_TARGET
#endif
)
{
	vec3 color = vec3(0.1, 0.1, 0.15);
    
    vec2 st = FragPos.xy/1024;
    st *= 250.0;
    vec2 ipos = floor(st);

    float strength = step(1.0, random(ipos));
	vec3 starColor = vec3(1.0, 1.0, 1.0) * strength * .7;
    color /= starColor;
    //color += vec3(random( ipos ));
    
    // Output to screen
    o_color = vec4(color,1.0);
}
