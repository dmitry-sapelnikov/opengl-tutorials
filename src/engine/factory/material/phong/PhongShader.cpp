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
uniform sampler2D diffuseSampler;
uniform sampler2D specularSampler;
uniform float shininess;
uniform vec3 viewPos;

struct LightColor
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight
{
	vec3 pos;
	LightColor color;
};

#define MAX_POINT_LIGHTS 4
uniform PointLight pointLights[MAX_POINT_LIGHTS];

// Inputs
in vec3 pos;
in vec3 normal;
in vec2 texCoord;

// Outputs
out vec4 outColor;

void main()
{
	vec3 norm = normalize(normal);
	for (int i = 0; i < MAX_POINT_LIGHTS; ++i)
	{
		vec3 geomDiffuse = texture(diffuseSampler, texCoord).rgb;

		// Ambient
		vec3 ambient = pointLights[i].color.ambient * geomDiffuse;

		// Diffuse
		vec3 lightDir = normalize(pointLights[i].pos - pos);
		vec3 diffuse = max(0.0f, dot(norm, lightDir)) * pointLights[i].color.diffuse * geomDiffuse;

		// Specular
		vec3 viewDir = normalize(viewPos - pos);
		vec3 reflectDir = reflect(-lightDir, norm);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
		vec3 specular = spec * pointLights[i].color.specular * texture(specularSampler, texCoord).rgb;

		outColor += vec4(ambient + diffuse + specular, 1.0f);
	}
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

	shader->setInt("diffuseSampler", 0);
	shader->setInt("specularSampler", 1);
	shader->setFloat("shininess", DEFAULT_SHINESS);

	bindModelViewProjectionShaderParameters(binding, "model", "view", "projection");
	binding->bind(SceneShaderBinding::Parameter::GEOMETRY_NORMAL_MATRIX, "normalMat");
	binding->bind(SceneShaderBinding::Parameter::CAMERA_POSITION, "viewPos");

	binding->bind(SceneShaderBinding::Parameter::POINT_LIGHT_POSITION, "pointLights.pos");
	binding->bind(SceneShaderBinding::Parameter::POINT_LIGHT_AMBIENT_COLOR, "pointLights.color.ambient");
	binding->bind(SceneShaderBinding::Parameter::POINT_LIGHT_DIFFUSE_COLOR, "pointLights.color.diffuse");
	binding->bind(SceneShaderBinding::Parameter::POINT_LIGHT_SPECULAR_COLOR, "pointLights.color.specular");

	return binding;
}

// End of the namespace gltut
}
