// Includes
#include <string>
#include "PhongShaderModelC.h"

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
uniform sampler2D directionalLightShadowSamplers[MAX_DIRECTIONAL_LIGHTS];
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
out vec4 shadowSpacePos[MAX_DIRECTIONAL_LIGHTS];
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
		shadowSpacePos[i] = directionalLights[i].shadowMatrix * vec4(pos, 1.0f);
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

// Inputs
in vec3 pos;
in vec3 normal;
in vec2 texCoord;

#if MAX_DIRECTIONAL_LIGHTS > 0
in vec4 shadowSpacePos[MAX_DIRECTIONAL_LIGHTS];
#endif

// Outputs
out vec4 outColor;

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
		float dot_diffuse = max(0.0f, dot(norm, lightDir));
		vec3 diffuse = dot_diffuse * directionalLights[i].color.diffuse * geomDiffuse;

		// Specular
		vec3 reflectDir = reflect(-lightDir, norm);
		float dot_specular = max(dot(viewDir, reflectDir), 0.0);
		float spec = pow(dot_specular, shininess);
		vec3 specular = spec * directionalLights[i].color.specular * texture(specularSampler, texCoord).rgb;

		// Shadow mapping
		vec3 projCoords = shadowSpacePos[i].xyz * (0.5 / shadowSpacePos[i].w) + 0.5;
		float closestDepth = texture(directionalLightShadowSamplers[i], projCoords.xy).r;
		float bias = 0.001;
		result += (diffuse + specular) * float(projCoords.z - bias < closestDepth);
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
			vec3 diffuse = max(0.0f, dot(norm, lightDir)) * spotLights[i].color.diffuse * geomDiffuse;
			
			// Specular
			vec3 reflectDir = reflect(-lightDir, norm);
			float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
			vec3 specular = spec * spotLights[i].color.specular * texture(specularSampler, texCoord).rgb;

			// Attenuation
			float attenuation = 1.0f / (
				1.0f +
				spotLights[i].linAttenuation * distance +
				spotLights[i].quadAttenuation * distance * distance);

			result += intensity * attenuation * (diffuse + specular);
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
	mMaxSpotLights(maxSpotLights)
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

	mShader = device->getShaders()->create(
		(shaderHeader + PHONG_VERTEX_SHADER).c_str(),
		(shaderHeader + PHONG_FRAGMENT_SHADER).c_str());

	GLTUT_CHECK(mShader, "Failed to create Phong shader");

	mShader->setInt("diffuseSampler", 0);
	mShader->setInt("specularSampler", 1);
	mShader->setFloat("shininess", DEFAULT_SHINESS);
	for (u32 i = 0; i < maxDirectionalLights; ++i)
	{
		mShader->setInt(
			("directionalLightShadowSamplers[" + std::to_string(i) + "]").c_str(),
			PhongShaderModel::TEXTURE_SLOTS_COUNT + i);
	}

	mMaterialBinding = renderer.createShaderMaterialBinding(mShader);
	GLTUT_CHECK(mMaterialBinding != nullptr, "Failed to create shader material binding");

	mMaterialBinding->bind(ShaderMaterialBinding::Parameter::GEOMETRY_MATRIX, "model");
	mMaterialBinding->bind(ShaderMaterialBinding::Parameter::GEOMETRY_NORMAL_MATRIX, "normalMat");

	mViewpointBinding = renderer.createShaderViewpointBinding(mShader);
	GLTUT_CHECK(mViewpointBinding != nullptr, "Failed to create shader viewpoint binding");

	mViewpointBinding->bind(ShaderViewpointBinding::Parameter::VIEW_MATRIX, "view");
	mViewpointBinding->bind(ShaderViewpointBinding::Parameter::PROJECTION_MATRIX, "projection");
	mViewpointBinding->bind(ShaderViewpointBinding::Parameter::POSITION, "viewPos");

	mSceneBinding = scene.createShaderBinding(mShader);
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
}

PhongShaderModelC::~PhongShaderModelC() noexcept
{
	if (mRenderer.getDevice() != nullptr)
	{
		mRenderer.getDevice()->getShaders()->remove(mShader);
	}
	mRenderer.removeShaderViewpointBinding(mViewpointBinding);
	mRenderer.removeShaderMaterialBinding(mMaterialBinding);
	mScene.removeShaderBinding(mSceneBinding);
}

// End of the namespace gltut
}
