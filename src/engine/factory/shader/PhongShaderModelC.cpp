// Includes
#include <string>
#include "PhongShaderModelC.h"
#include "./StandardShaderBinding.h"

namespace gltut
{
//	 Constants and enums

static const char* LIGHT_UNIFORMS = R"(
struct Color
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

#if MAX_DIRECTIONAL_LIGHTS > 0
struct DirectionalLight
{
	Color color;
	vec3 dir;
	mat4 shadowMatrix;
};
uniform DirectionalLight directionalLights[MAX_DIRECTIONAL_LIGHTS];
#endif

#if MAX_POINT_LIGHTS > 0
struct PointLight
{
	Color color;
	vec3 pos;
	float linAttenuation;
	float quadAttenuation;
};

uniform PointLight pointLights[MAX_POINT_LIGHTS];
#endif

#if MAX_SPOT_LIGHTS > 0
struct SpotLight
{
	Color color;
	vec3 pos;
	vec3 dir;
	float innerAngleCos;
	float outerAngleCos;
	float linAttenuation;
	float quadAttenuation;
	mat4 shadowMatrix;
};

uniform SpotLight spotLights[MAX_SPOT_LIGHTS];
#endif

)";

// Vertex shader source code for Phong shading
static const char* PHONG_VERTEX_SHADER = R"(
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

#if MAX_DIRECTIONAL_LIGHTS > 0
out vec4 directionalShadowSpacePos[MAX_DIRECTIONAL_LIGHTS];
#endif

#if MAX_SPOT_LIGHTS > 0
out vec4 spotShadowSpacePos[MAX_SPOT_LIGHTS];
#endif

void main()
{
	vec4 modelPos = model * vec4(inPos, 1.0f);
	gl_Position = projection * view * modelPos;
	pos = vec3(modelPos);
	normal = normalMat * inNormal;
	texCoord = inTexCoord;

#if MAX_DIRECTIONAL_LIGHTS > 0
	for (int i = 0; i < MAX_DIRECTIONAL_LIGHTS; ++i)
	{
		directionalShadowSpacePos[i] = directionalLights[i].shadowMatrix * vec4(pos, 1.0f);
	}
#endif

#if MAX_SPOT_LIGHTS > 0
	for (int i = 0; i < MAX_SPOT_LIGHTS; ++i)
	{
		spotShadowSpacePos[i] = spotLights[i].shadowMatrix * vec4(pos, 1.0f);
	}
#endif
})";

// Fragment shader source code for Phong shading
static const char* PHONG_FRAGMENT_SHADER = R"(

// Uniforms
uniform sampler2D diffuseSampler;
uniform sampler2D specularSampler;
uniform float shininess;
uniform vec3 viewPos;
uniform float minShadowMapBias;
uniform float maxShadowMapBias;

// Inputs
in vec3 pos;
in vec3 normal;
in vec2 texCoord;

#if MAX_DIRECTIONAL_LIGHTS > 0
in vec4 directionalShadowSpacePos[MAX_DIRECTIONAL_LIGHTS];
#endif

#if MAX_SPOT_LIGHTS > 0
in vec4 spotShadowSpacePos[MAX_SPOT_LIGHTS];
#endif

#if MAX_DIRECTIONAL_LIGHTS > 0 || MAX_SPOT_LIGHTS > 0
uniform sampler2D shadowSamplers[MAX_DIRECTIONAL_LIGHTS + MAX_SPOT_LIGHTS];
#endif

// Outputs
out vec4 outColor;

float getShadowFactor(vec4 shadowSpacePos, int shadowInd, float normalLightDot)
{
	if (shadowSpacePos.w <= 0.0f)
	{
		return 1.0f;
	}

	vec3 projCoords = shadowSpacePos.xyz * (0.5 / shadowSpacePos.w) + 0.5;
	vec2 texelSize = 1.0 / textureSize(shadowSamplers[shadowInd], 0);
	float bias = mix(minShadowMapBias, maxShadowMapBias, 1.0 - abs(normalLightDot));
	float shadow = 0.0f;
	for (int x = -1; x <= 1; ++x)
	{
		for (int y = -1; y <= 1; ++y)
		{
			float closestDepth = texture(
				shadowSamplers[shadowInd],
				projCoords.xy + vec2(x, y) * texelSize).r;
			shadow += float(projCoords.z - bias < closestDepth);
		}
	}
	shadow *= 1.0 / 9.0;
	return shadow;
}

void main()
{
	vec3 result = vec3(0.0f);

#if MAX_DIRECTIONAL_LIGHTS + MAX_POINT_LIGHTS + MAX_SPOT_LIGHTS > 0
	vec3 norm = normalize(normal);
	vec3 viewDir = normalize(viewPos - pos);
	vec3 geomDiffuse = texture(diffuseSampler, texCoord).rgb;
#endif

#if MAX_DIRECTIONAL_LIGHTS > 0
	for (int i = 0; i < MAX_DIRECTIONAL_LIGHTS; ++i)
	{
		// Ambient
		result += directionalLights[i].color.ambient * geomDiffuse;

		// Diffuse
		vec3 lightDir = -directionalLights[i].dir;
		float normalLightDot = dot(norm, lightDir);
		vec3 diffuse = max(0.0f, normalLightDot) * directionalLights[i].color.diffuse * geomDiffuse;

		// Specular
		vec3 reflectDir = reflect(-lightDir, norm);
		float dot_specular = max(dot(viewDir, reflectDir), 0.0);
		float spec = pow(dot_specular, shininess);
		vec3 specular = spec * directionalLights[i].color.specular * texture(specularSampler, texCoord).rgb;
		result += (diffuse + specular) * getShadowFactor(
			directionalShadowSpacePos[i],
			i,
			normalLightDot);
	}
#endif

#if MAX_POINT_LIGHTS > 0
	for (int i = 0; i < MAX_POINT_LIGHTS; ++i)
	{
		// Ambient
		vec3 ambient = pointLights[i].color.ambient * geomDiffuse;

		// Diffuse
		vec3 lightDir = (pointLights[i].pos - pos);
		float distance = length(lightDir);
		lightDir /= distance;
		vec3 diffuse = max(0.0f, dot(norm, lightDir)) * pointLights[i].color.diffuse * geomDiffuse;

		// Specular
		vec3 reflectDir = reflect(-lightDir, norm);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
		vec3 specular = spec * pointLights[i].color.specular * texture(specularSampler, texCoord).rgb;

		// Attenuation
		float attenuation = 1.0f / (
			1.0f +
			pointLights[i].linAttenuation * distance +
			pointLights[i].quadAttenuation * distance * distance);

		result += ambient + attenuation * (diffuse + specular);
	}
#endif

#if MAX_SPOT_LIGHTS > 0
	for (int i = 0; i < MAX_SPOT_LIGHTS; ++i)
	{
		// Ambient
		result += spotLights[i].color.ambient * geomDiffuse;

		vec3 lightDir = (spotLights[i].pos - pos);
		float distance = length(lightDir);
		lightDir /= distance;

		float theta = dot(-lightDir, spotLights[i].dir);
		
		float innerAngleCos = spotLights[i].innerAngleCos;
		float outerAngleCos = spotLights[i].outerAngleCos;
		if (theta > outerAngleCos)
		{
			float intensity = clamp((theta - outerAngleCos) / (innerAngleCos - outerAngleCos), 0.0, 1.0);

			// Diffuse
			float normalLightDot = dot(norm, lightDir);
			vec3 diffuse = max(0.0f, normalLightDot) * spotLights[i].color.diffuse * geomDiffuse;
			
			// Specular
			vec3 reflectDir = reflect(-lightDir, norm);
			float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
			vec3 specular = spec * spotLights[i].color.specular * texture(specularSampler, texCoord).rgb;

			// Attenuation
			float attenuation = 1.0f / (
				1.0f +
				spotLights[i].linAttenuation * distance +
				spotLights[i].quadAttenuation * distance * distance);

			// Shadow factor
			float shadowFactor = 1.0f;
			if (spotLights[i].shadowMatrix[3][3] > 0.0f)
			{
				shadowFactor = getShadowFactor(
					spotShadowSpacePos[i],
					MAX_DIRECTIONAL_LIGHTS + i,
					normalLightDot);
			}

			result += intensity * (attenuation * shadowFactor) * (diffuse + specular);
		}
	}
#endif
	outColor = vec4(result, 1.0f);
})";

// Global classes
PhongShaderModelC::PhongShaderModelC(
	Renderer& renderer,
	Scene& scene,
	u32 maxDirectionalLights,
	u32 maxPointLights,
	u32 maxSpotLights) :

	mRenderer(renderer),
	mScene(scene),
	mMaxDirectionalLights(maxDirectionalLights),
	mMaxPointLights(maxPointLights),
	mMaxSpotLights(maxSpotLights),
	mMinShadowMapBias(0),
	mMaxShadowMapBias(0)
{
	GLTUT_CHECK(
		mMaxDirectionalLights + mMaxDirectionalLights + mMaxSpotLights > 0,
		"At least one amount of lights must be greater than 0");

	GraphicsDevice* device = renderer.getDevice();
	GLTUT_CHECK(device, "Failed to get graphics device");

	std::string shaderHeader = "#version 330 core\n";
	shaderHeader += "#define MAX_DIRECTIONAL_LIGHTS " + std::to_string(maxDirectionalLights) + "\n";
	shaderHeader += "#define MAX_POINT_LIGHTS " + std::to_string(maxPointLights) + "\n";
	shaderHeader += "#define MAX_SPOT_LIGHTS " + std::to_string(maxSpotLights) + "\n";
	shaderHeader += LIGHT_UNIFORMS;

	mRendererBinding = createStandardShaderBinding(
		mRenderer,
		(shaderHeader + PHONG_VERTEX_SHADER).c_str(),
		(shaderHeader + PHONG_FRAGMENT_SHADER).c_str());

	GLTUT_CHECK(mRendererBinding != nullptr, "Failed to create Phong shader binding");
	auto* shader = mRendererBinding->getShader();
	GLTUT_CHECK(shader != nullptr, "Invalid shader pointer");

	mRendererBinding->bind(ShaderRendererBinding::Parameter::VIEWPOINT_POSITION, "viewPos");
	mRendererBinding->bind(ShaderRendererBinding::Parameter::GEOMETRY_NORMAL_MATRIX, "normalMat");

	shader->setInt("diffuseSampler", 0);
	shader->setInt("specularSampler", 1);
	shader->setFloat("shininess", DEFAULT_SHINESS);
	for (u32 i = 0; i < maxDirectionalLights + maxSpotLights; ++i)
	{
		shader->setInt(
			("shadowSamplers[" + std::to_string(i) + "]").c_str(),
			PhongShaderModel::TEXTURE_SLOTS_COUNT + i);
	}

	mSceneBinding = scene.createShaderBinding(shader);
	GLTUT_CHECK(mSceneBinding != nullptr, "Failed to create scene shader binding");

	mSceneBinding->bind(SceneShaderBinding::Parameter::DIRECTIONAL_LIGHT_DIRECTION, "directionalLights.dir");
	mSceneBinding->bind(SceneShaderBinding::Parameter::DIRECTIONAL_LIGHT_AMBIENT_COLOR, "directionalLights.color.ambient");
	mSceneBinding->bind(SceneShaderBinding::Parameter::DIRECTIONAL_LIGHT_DIFFUSE_COLOR, "directionalLights.color.diffuse");
	mSceneBinding->bind(SceneShaderBinding::Parameter::DIRECTIONAL_LIGHT_SPECULAR_COLOR, "directionalLights.color.specular");
	mSceneBinding->bind(SceneShaderBinding::Parameter::DIRECTIONAL_LIGHT_SHADOW_MATRIX, "directionalLights.shadowMatrix");

	mSceneBinding->bind(SceneShaderBinding::Parameter::POINT_LIGHT_POSITION, "pointLights.pos");
	mSceneBinding->bind(SceneShaderBinding::Parameter::POINT_LIGHT_AMBIENT_COLOR, "pointLights.color.ambient");
	mSceneBinding->bind(SceneShaderBinding::Parameter::POINT_LIGHT_DIFFUSE_COLOR, "pointLights.color.diffuse");
	mSceneBinding->bind(SceneShaderBinding::Parameter::POINT_LIGHT_SPECULAR_COLOR, "pointLights.color.specular");
	mSceneBinding->bind(SceneShaderBinding::Parameter::POINT_LIGHT_LINEAR_ATTENUATION, "pointLights.linAttenuation");
	mSceneBinding->bind(SceneShaderBinding::Parameter::POINT_LIGHT_QUADRATIC_ATTENUATION, "pointLights.quadAttenuation");

	mSceneBinding->bind(SceneShaderBinding::Parameter::SPOT_LIGHT_POSITION, "spotLights.pos");
	mSceneBinding->bind(SceneShaderBinding::Parameter::SPOT_LIGHT_DIRECTION, "spotLights.dir");
	mSceneBinding->bind(SceneShaderBinding::Parameter::SPOT_LIGHT_INNER_ANGLE_COS, "spotLights.innerAngleCos");
	mSceneBinding->bind(SceneShaderBinding::Parameter::SPOT_LIGHT_OUTER_ANGLE_COS, "spotLights.outerAngleCos");
	mSceneBinding->bind(SceneShaderBinding::Parameter::SPOT_LIGHT_AMBIENT_COLOR, "spotLights.color.ambient");
	mSceneBinding->bind(SceneShaderBinding::Parameter::SPOT_LIGHT_DIFFUSE_COLOR, "spotLights.color.diffuse");
	mSceneBinding->bind(SceneShaderBinding::Parameter::SPOT_LIGHT_SPECULAR_COLOR, "spotLights.color.specular");
	mSceneBinding->bind(SceneShaderBinding::Parameter::SPOT_LIGHT_LINEAR_ATTENUATION, "spotLights.linAttenuation");
	mSceneBinding->bind(SceneShaderBinding::Parameter::SPOT_LIGHT_QUADRATIC_ATTENUATION, "spotLights.quadAttenuation");
	mSceneBinding->bind(SceneShaderBinding::Parameter::SPOT_LIGHT_SHADOW_MATRIX, "spotLights.shadowMatrix");

	setMaxShadowMapBias(DEFAULT_MAX_SHADOW_MAP_BIAS);
	setMinShadowMapBias(DEFAULT_MIN_SHADOW_MAP_BIAS);
}

PhongShaderModelC::~PhongShaderModelC() noexcept
{
	Shader* shader = mRendererBinding != nullptr ?
		mRendererBinding->getShader() :
		nullptr;
	mRenderer.removeShaderBinding(mRendererBinding);
	mScene.removeShaderBinding(mSceneBinding);
	mRenderer.getDevice()->getShaders()->remove(shader);
}

void PhongShaderModelC::setMinShadowMapBias(float bias) noexcept
{
	mMinShadowMapBias = clamp(bias, 0.0f, mMaxShadowMapBias);
	mRendererBinding->getShader()->setFloat(
		"minShadowMapBias", mMinShadowMapBias);
}

void PhongShaderModelC::setMaxShadowMapBias(float bias) noexcept
{
	mMaxShadowMapBias = std::max(0.0f, bias);
	mRendererBinding->getShader()->setFloat(
		"maxShadowMapBias", mMaxShadowMapBias);
	setMinShadowMapBias(mMinShadowMapBias);
}

// End of the namespace gltut
}
