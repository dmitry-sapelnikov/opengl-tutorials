// Includes
#include <string>
#include "FlatColorShader.h"

namespace gltut
{
//	 Constants and enums
// Vertex shader source code for flat color shading
static const char* FLAT_COLOR_VERTEX_SHADER = R"(
#version 330 core

// Uniforms
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// Inputs
layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTexCoord;

// Outputs
out vec2 texCoord;

void main()
{
	gl_Position = projection * view * model * vec4(inPos, 1.0f);
	texCoord = inTexCoord;
})";

// Fragment shader source code for flat color shading
static const char* FLAT_COLOR_FRAGMENT_SHADER = R"(
#version 330 core

// Uniforms
uniform sampler2D colorSampler;

// Inputs
in vec2 texCoord;

// Outputs
out vec4 outColor;

void main()
{
	outColor = texture(colorSampler, texCoord);
})";

// Global functions
SceneShaderBinding* createFlatColorShader(
	Renderer& renderer,
	Scene& scene) noexcept
{
	Shader* shader = renderer.createShader(
		FLAT_COLOR_VERTEX_SHADER,
		FLAT_COLOR_FRAGMENT_SHADER);

	if (shader == nullptr)
	{
		return nullptr;
	}

	SceneShaderBinding* binding = scene.createShaderBinding(shader);
	if (binding == nullptr)
	{
		renderer.removeShader(shader);
		return nullptr;
	}

	shader->setInt("colorSampler", 0);
	bindModelViewProjectionShaderParameters(binding, "model", "view", "projection");
	return binding;
}

// End of the namespace gltut
}
