// Includes
#include <string>
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

#if MAX_DIRECTIONAL_LIGHTS > 0
struct DirectionalLight
{
	LightColor color;
	vec3 dir;
};
uniform DirectionalLight directionalLights[MAX_DIRECTIONAL_LIGHTS];
#endif

#if MAX_POINT_LIGHTS > 0
struct PointLight
{
	LightColor color;
	vec3 pos;
};

uniform PointLight pointLights[MAX_POINT_LIGHTS];
#endif

#if MAX_SPOT_LIGHTS > 0
struct SpotLight
{
	LightColor color;
	vec3 pos;
	vec3 dir;
	float innerAngleCos;
	float outerAngleCos;
};

uniform SpotLight spotLights[MAX_SPOT_LIGHTS];
#endif

// Inputs
in vec3 pos;
in vec3 normal;
in vec2 texCoord;

// Outputs
out vec4 outColor;

void main()
{
	vec3 norm = normalize(normal);
	vec3 viewDir = normalize(viewPos - pos);

	vec3 geomDiffuse = texture(diffuseSampler, texCoord).rgb;
	vec3 result = vec3(0.0f);

#if MAX_DIRECTIONAL_LIGHTS > 0
	for (int i = 0; i < MAX_DIRECTIONAL_LIGHTS; ++i)
	{
		// Ambient
		vec3 ambient = directionalLights[i].color.ambient * geomDiffuse;

		// Diffuse
		vec3 lightDir = normalize(-directionalLights[i].dir);
		vec3 diffuse = max(0.0f, dot(norm, lightDir)) * directionalLights[i].color.diffuse * geomDiffuse;

		// Specular
		vec3 reflectDir = reflect(-lightDir, norm);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
		vec3 specular = spec * directionalLights[i].color.specular * texture(specularSampler, texCoord).rgb;

		result += ambient + diffuse + specular;
	}
#endif

#if MAX_POINT_LIGHTS > 0
	for (int i = 0; i < MAX_POINT_LIGHTS; ++i)
	{
		// Ambient
		vec3 ambient = pointLights[i].color.ambient * geomDiffuse;

		// Diffuse
		vec3 lightDir = normalize(pointLights[i].pos - pos);
		vec3 diffuse = max(0.0f, dot(norm, lightDir)) * pointLights[i].color.diffuse * geomDiffuse;

		// Specular
		vec3 reflectDir = reflect(-lightDir, norm);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
		vec3 specular = spec * pointLights[i].color.specular * texture(specularSampler, texCoord).rgb;

		result += ambient + diffuse + specular;
	}
#endif

#if MAX_SPOT_LIGHTS > 0
	for (int i = 0; i < MAX_SPOT_LIGHTS; ++i)
	{
		// Ambient
		result += spotLights[i].color.ambient * geomDiffuse;

		vec3 lightDir = normalize(spotLights[i].pos - pos);

		float theta = dot(-lightDir, spotLights[i].dir);
		
		float innerAngleCos = spotLights[i].innerAngleCos;
		float outerAngleCos = spotLights[i].outerAngleCos;
		if (theta > outerAngleCos)
		{
			float intensity = clamp((theta - outerAngleCos) / (innerAngleCos - outerAngleCos), 0.0, 1.0);

			// Diffuse
			vec3 diffuse = max(0.0f, dot(norm, lightDir)) * spotLights[i].color.diffuse * geomDiffuse;
			
			// Specular
			vec3 reflectDir = reflect(-lightDir, norm);
			float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
			vec3 specular = spec * spotLights[i].color.specular * texture(specularSampler, texCoord).rgb;
			result += intensity * (diffuse + specular);
		}
	}
#endif
	outColor = vec4(result, 1.0f);
})";

// Default shininess value
static constexpr float DEFAULT_SHINESS = 32.0f;

// Global functions
SceneShaderBinding* createPhongShader(
	Renderer& renderer,
	Scene& scene,
	u32 maxDirectionalLights,
	u32 maxPointLights,
	u32 maxSpotLights) noexcept
{
	// No lights, no shader
	if (maxDirectionalLights + maxPointLights + maxSpotLights == 0)
	{
		return nullptr;
	}

	std::string fragmentShader = "#version 330 core\n";
	fragmentShader += "#define MAX_DIRECTIONAL_LIGHTS " + std::to_string(maxDirectionalLights) + "\n";
	fragmentShader += "#define MAX_POINT_LIGHTS " + std::to_string(maxPointLights) + "\n";
	fragmentShader += "#define MAX_SPOT_LIGHTS " + std::to_string(maxSpotLights) + "\n";
	fragmentShader += PHONG_FRAGMENT_SHADER;

	Shader* shader = renderer.createShader(PHONG_VERTEX_SHADER, fragmentShader.c_str());
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

	binding->bind(SceneShaderBinding::Parameter::DIRECTIONAL_LIGHT_DIRECTION, "directionalLights.dir");
	binding->bind(SceneShaderBinding::Parameter::DIRECTIONAL_LIGHT_AMBIENT_COLOR, "directionalLights.color.ambient");
	binding->bind(SceneShaderBinding::Parameter::DIRECTIONAL_LIGHT_DIFFUSE_COLOR, "directionalLights.color.diffuse");
	binding->bind(SceneShaderBinding::Parameter::DIRECTIONAL_LIGHT_SPECULAR_COLOR, "directionalLights.color.specular");

	binding->bind(SceneShaderBinding::Parameter::POINT_LIGHT_POSITION, "pointLights.pos");
	binding->bind(SceneShaderBinding::Parameter::POINT_LIGHT_AMBIENT_COLOR, "pointLights.color.ambient");
	binding->bind(SceneShaderBinding::Parameter::POINT_LIGHT_DIFFUSE_COLOR, "pointLights.color.diffuse");
	binding->bind(SceneShaderBinding::Parameter::POINT_LIGHT_SPECULAR_COLOR, "pointLights.color.specular");

	binding->bind(SceneShaderBinding::Parameter::SPOT_LIGHT_POSITION, "spotLights.pos");
	binding->bind(SceneShaderBinding::Parameter::SPOT_LIGHT_DIRECTION, "spotLights.dir");
	binding->bind(SceneShaderBinding::Parameter::SPOT_LIGHT_INNER_ANGLE_COS, "spotLights.innerAngleCos");
	binding->bind(SceneShaderBinding::Parameter::SPOT_LIGHT_OUTER_ANGLE_COS, "spotLights.outerAngleCos");
	binding->bind(SceneShaderBinding::Parameter::SPOT_LIGHT_AMBIENT_COLOR, "spotLights.color.ambient");
	binding->bind(SceneShaderBinding::Parameter::SPOT_LIGHT_DIFFUSE_COLOR, "spotLights.color.diffuse");
	binding->bind(SceneShaderBinding::Parameter::SPOT_LIGHT_SPECULAR_COLOR, "spotLights.color.specular");

	return binding;
}

// End of the namespace gltut
}
