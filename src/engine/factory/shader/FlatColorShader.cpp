// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

// Includes
#include "FlatColorShader.h"

namespace gltut
{

namespace
{
// Local constants and enums
// Vertex shader source code for flat color shading
const char* FLAT_COLOR_VERTEX_SHADER = R"(
#version 330 core

// Uniforms
layout (std140) uniform ViewProjection
{
	mat4 view;
	mat4 projection;
};
uniform mat4 model;

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
const char* FLAT_COLOR_FRAGMENT_SHADER = R"(
#version 330 core

// Uniforms
uniform sampler2D colorSampler;
uniform float transparencyThreshold;

// Inputs
in vec2 texCoord;

// Outputs
out vec4 outColor;

void main()
{
	outColor = texture(colorSampler, texCoord);
	if (transparencyThreshold != 0.0 && outColor.a < transparencyThreshold)
		discard;
})";

// End of anonymous namespace
}

// Global functions
ShaderRendererBinding* createFlatColorShader(Renderer& renderer) noexcept
{
	ShaderRendererBinding* result = createStandardShaderBinding(
		&renderer,
		FLAT_COLOR_VERTEX_SHADER,
		FLAT_COLOR_FRAGMENT_SHADER,
		"model",
		nullptr,
		nullptr); // Don't need view, projection - using uniform buffer

	if (result == nullptr)
	{
		return result;
	}

	result->getTarget()->setInt("colorSampler", 0);
	result->getTarget()->setFloat("transparencyThreshold", 0.0f);
	result->getTarget()->setUniformBlockBindingPoint(
		"ViewProjection",
		0); // Binding point 0 for view/projection matrix uniform buffer
	return result;
}

// End of the namespace gltut
}
