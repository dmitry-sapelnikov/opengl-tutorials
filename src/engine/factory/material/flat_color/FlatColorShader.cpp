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
ShaderMaterialBinding* createFlatColorShader(Renderer& renderPipeline) noexcept
{
	Shader* shader = nullptr;
	ShaderViewpointBinding* viewpointBinding = nullptr;
	ShaderMaterialBinding* materialBinding = nullptr;

	GLTUT_CATCH_ALL_BEGIN
		Shader* shader = renderPipeline.getDevice()->getShaders()->create(
			FLAT_COLOR_VERTEX_SHADER,
			FLAT_COLOR_FRAGMENT_SHADER);

		GLTUT_CHECK(shader != nullptr, "Cannot create a flat color shader");
		shader->setInt("colorSampler", 0);

		viewpointBinding = renderPipeline.createShaderViewpointBinding(shader);
		GLTUT_CHECK(viewpointBinding != nullptr, "Cannot create a shader viewpoint binding");

		viewpointBinding->bind(ShaderViewpointBinding::Parameter::VIEW_MATRIX, "view");
		viewpointBinding->bind(ShaderViewpointBinding::Parameter::PROJECTION_MATRIX, "projection");

		materialBinding = renderPipeline.createShaderMaterialBinding(shader);
		GLTUT_CHECK(materialBinding != nullptr, "Cannot create a shader material binding");
		materialBinding->bind(ShaderMaterialBinding::Parameter::GEOMETRY_MATRIX, "model");

		return materialBinding;
	GLTUT_CATCH_ALL_END("Cannot create a flat color shader");

	if (materialBinding != nullptr)
	{
		renderPipeline.removeShaderMaterialBinding(materialBinding);
	}

	if (viewpointBinding != nullptr)
	{
		renderPipeline.removeShaderViewpointBinding(viewpointBinding);
	}

	if (shader != nullptr)
	{
		renderPipeline.getDevice()->getShaders()->remove(shader);
	}

	return nullptr;
}

// End of the namespace gltut
}
