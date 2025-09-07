// Includes
#include "DepthShader.h"

namespace gltut
{
//	 Constants and enums
// Vertex shader source code for flat color shading
static const char* DEPTH_VERTEX_SHADER = R"(
#version 330 core

// Uniforms
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// Inputs
layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTexCoord;

void main()
{
	gl_Position = projection * view * model * vec4(inPos, 1.0f);
})";

// Fragment shader source code for flat color shading
static const char* DEPTH_FRAGMENT_SHADER = R"(
#version 330 core
void main()
{
})";

// Global functions
ShaderRendererBinding* createDepthShader(Renderer& renderer) noexcept
{
	return createStandardShaderBinding(
		&renderer,
		DEPTH_VERTEX_SHADER,
		DEPTH_FRAGMENT_SHADER);
}

// End of the namespace gltut
}
