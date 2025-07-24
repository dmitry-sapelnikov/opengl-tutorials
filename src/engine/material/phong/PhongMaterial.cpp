// Includes
#include "engine/material/PhongMaterial.h"

namespace gltut
{
//	 Constants and enums

// Vertex shader source code for Phong shading
static const char* PHONG_VERTEX_SHADER = R"(
#version 330 core
layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTexCoord;

out vec3 pos;
out vec3 normal;
out vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform vec3 viewPos;
uniform mat4 projection;
uniform mat3 normalMat;

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

in vec3 pos;
in vec3 normal;

in vec2 texCoord;

out vec4 outColor;

uniform sampler2D objectColorSampler;

uniform vec3 lightColor;

uniform vec3 lightPos;
uniform vec3 viewPos;

uniform float shininess;

void main()
{
	vec3 norm = normalize(normal);

	float ambientStrength = 0.2f;
	vec3 ambient = ambientStrength * lightColor;

	vec3 lightDirection = normalize(lightPos - pos);
	vec3 diffuse = max(0.0f, dot(norm, lightDirection)) * lightColor;

	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPos - pos);
	vec3 reflectDir = reflect(-lightDirection, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
	vec3 specular = specularStrength * spec * lightColor;

	outColor =  vec4((ambient + diffuse + specular) * texture(objectColorSampler, texCoord).rgb, 1.0f);
})";

// Default shininess value
static constexpr float DEFAULT_SHINESS = 32.0f;

// Global functions
Shader* createPhongShader(Renderer& renderer) noexcept
{
	Shader* result = renderer.createShader(PHONG_VERTEX_SHADER, PHONG_FRAGMENT_SHADER);
	if (result == nullptr)
	{
		return nullptr;
	}

	result->setMatrixName(Shader::Matrix::MODEL, "model");
	result->setMatrixName(Shader::Matrix::VIEW, "view");
	result->setMatrixName(Shader::Matrix::PROJECTION, "projection");
	result->setMatrixName(Shader::Matrix::NORMAL, "normalMat");
	result->setFloat("shininess", DEFAULT_SHINESS);

	return result;
}

void setPhongMaterialParameters(
	Material& material,
	Texture* diffuse,
	Texture* ambient,
	Texture* specular,
	float shininess) noexcept
{
	material.setTexture(diffuse, 0);
	material.setTexture(ambient, 1);
	material.setTexture(specular, 2);
	material.getShaderArguments()->setFloat("shininess", shininess);
}

// End of the namespace gltut
}
