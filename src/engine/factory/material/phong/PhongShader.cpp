// Includes
#include "PhongShader.h"


namespace gltut
{
//	 Constants and enums

// Vertex shader source code for Phong shading
static const char* PHONG_VERTEX_SHADER = R"(
#version 330 core

// Uniforms
uniform mat4 model;
uniform mat4 view;
uniform vec3 viewPos;
uniform mat4 projection;
uniform mat3 normalMat;

// Inputs
layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTexCoord;

// Outputs
out vec3 pos;
out vec3 normal;
out vec2 texCoord;

void main()
{
	gl_Position = projection * view * model * vec4(inPos, 1.0f);
	pos = vec3(model * vec4(inPos, 1.0f));
	normal = normalMat * inNormal;
	texCoord = inTexCoord;
})";

// Fragment shader source code for Phong shading
static const char* PHONG_FRAGMENT_SHADER = R"(
#version 330 core

// Uniforms
uniform sampler2D ambientSampler;
uniform sampler2D diffuseSampler;
uniform sampler2D specularSampler;

uniform float shininess;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

// Inputs
in vec3 pos;
in vec3 normal;
in vec2 texCoord;

// Outputs
out vec4 outColor;

void main()
{
	vec3 norm = normalize(normal);

	// Ambient
	vec3 ambient = lightColor * texture(ambientSampler, texCoord).rgb;

	// Diffuse
	vec3 lightDir = normalize(lightPos - pos);
	vec3 diffuse = max(0.0f, dot(norm, lightDir)) * lightColor * texture(diffuseSampler, texCoord).rgb;

	// Specular
	vec3 viewDir = normalize(viewPos - pos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
	vec3 specular = spec * lightColor * texture(specularSampler, texCoord).rgb;

	outColor = vec4(ambient + diffuse + specular, 1.0f);
})";

// Default shininess value
static constexpr float DEFAULT_SHINESS = 32.0f;

// Global functions
SceneShaderBinding* createPhongShader(Renderer& renderer, Scene& scene) noexcept
{
	Shader* shader = renderer.createShader(PHONG_VERTEX_SHADER, PHONG_FRAGMENT_SHADER);
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

	shader->setInt("ambientSampler", 0);
	shader->setInt("diffuseSampler", 1);
	shader->setInt("specularSampler", 2);
	shader->setFloat("shininess", DEFAULT_SHINESS);

	bindModelViewProjectionShaderParameters(binding, "model", "view", "projection");
	binding->bind(SceneShaderBinding::Parameter::NODE_NORMAL_MATRIX, "normalMat");
	binding->bind(SceneShaderBinding::Parameter::CAMERA_POSITION, "viewPos");

	return binding;
}

// End of the namespace gltut
}
