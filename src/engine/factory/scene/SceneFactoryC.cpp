// Includes
#include "SceneFactoryC.h"

namespace gltut
{

namespace
{
// Local constants
/// Cubemap vertex shader
const char* CUBEMAP_VERTEX_SHADER = R"(
#version 330 core

uniform mat4 view;
uniform mat4 projection;

layout(location = 0) in vec3 position;
out vec3 texCoords;

void main()
{
	texCoords = position;
	// Remove the translation part of the view matrix
	vec3 viewPos = (view * vec4(position, 0.0)).xyz;

	vec4 pos = projection * vec4(viewPos, 1.0);
	// A trick to set depth to 1.0
	gl_Position = pos.xyww;
})";

/// Cubemap fragment shader
static const char* CUBEMAP_FRAGMENT_SHADER = R"(
#version 330 core
uniform samplerCube skyboxSampler;

in vec3 texCoords;
out vec4 outColor;

void main()
{
	outColor = texture(skyboxSampler, texCoords);
})";

// End of the anonymous namespace
}

// Global classes
ShadowMap* SceneFactoryC::createShadowMap(
	const LightNode* light,
	const RenderObject* shadowCaster,
	float frustumSize,
	float frustumNear,
	float frustumFar,
	u32 shadowMapSize) noexcept
{
	if (light == nullptr || shadowCaster == nullptr ||
		light->getType() == LightNode::Type::POINT)
	{
		return nullptr;
	}

	ShadowMap* result = nullptr;
	GLTUT_CATCH_ALL_BEGIN
	if (auto findResult = mShadowMaps.find(light);
		findResult != mShadowMaps.end())
	{
		result = &findResult->second;
	}
	else
	{
		switch (light->getType())
		{
		case LightNode::Type::DIRECTIONAL:
		{
			// Create a new shadow map
			result = &mShadowMaps.try_emplace(
				light,
				mRenderer,
				*light,
				*shadowCaster,
				frustumSize,
				frustumNear,
				frustumFar,
				shadowMapSize).first->second;
		}
		break;

		case LightNode::Type::SPOT:
		{
			result = &mShadowMaps.try_emplace(
				light,
				mRenderer,
				*light,
				*shadowCaster,
				frustumNear,
				frustumFar,
				shadowMapSize).first->second;
		}
		break;

			GLTUT_UNEXPECTED_SWITCH_DEFAULT_CASE(light->getType())
		}
	}
	GLTUT_CATCH_ALL_END("Failed to create shadow map for the light");
	return result;
}

bool SceneFactoryC::createSkybox(
	const TextureCubemap* cubemapTexture,
	const Viewpoint* viewpoint,
	const Rectangle2u* viewport) noexcept
{
	GLTUT_ASSERT(cubemapTexture != nullptr);
	GLTUT_ASSERT(viewpoint != nullptr);
	if (cubemapTexture == nullptr || viewpoint == nullptr)
	{
		return false;
	}

	bool result = false;
	try
	{
		if (mSkyboxCube == nullptr)
		{
			mSkyboxCube = mGeometryFactory.createBox(gltut::Vector3(1.0f));
			GLTUT_CHECK(mSkyboxCube != nullptr, "Failed to create skybox geometry");
		}

		Material* skyboxMaterial = createSkyboxMaterial(*cubemapTexture);
		GLTUT_CHECK(skyboxMaterial != nullptr, "Failed to create skybox material");

		gltut::RenderGeometry* skyboxRenderGeometry = mRenderer.createGeometry(
			mSkyboxCube,
			skyboxMaterial,
			{});
		GLTUT_CHECK(skyboxRenderGeometry != nullptr, "Failed to create skybox render geometry");

		gltut::RenderPass* skyboxPass = mRenderer.createPass(
			viewpoint,
			skyboxRenderGeometry,
			mRenderer.getDevice()->getFramebuffers()->getDefault(),
			0,		 // Material pass
			nullptr, // No clear color
			false,	 // No depth clearing
			nullptr	 // Full viewport
		);

		GLTUT_CHECK(skyboxPass != nullptr, "Failed to create skybox render pass");
		// Set the depth function to less equal since the z-buffer is filled with 1.0 and
		// we force the skybox depth to 1.0 in the vertex shader
		skyboxPass->setDepthTest(DepthTestMode::LEQUAL);
		result = true;
	}
	GLTUT_CATCH_ALL("Failed to create skybox")
	return result;
}

gltut::Material* SceneFactoryC::createSkyboxMaterial(const TextureCubemap& cubemapTexture)
{
	if (mSkyboxShaderBinding == nullptr)
	{
		gltut::Shader* skyboxShader = mRenderer.getDevice()->getShaders()->create(
			CUBEMAP_VERTEX_SHADER,
			CUBEMAP_FRAGMENT_SHADER);
		GLTUT_CHECK(skyboxShader != nullptr, "Failed to create skybox shader");

		skyboxShader->setInt("skyboxSampler", 0);

		mSkyboxShaderBinding = mRenderer.createShaderBinding(skyboxShader);
		GLTUT_CHECK(mSkyboxShaderBinding != nullptr, "Failed to create skybox shader binding");

		mSkyboxShaderBinding->bind(
			gltut::RendererBinding::Parameter::VIEWPOINT_VIEW_MATRIX,
			"view");

		mSkyboxShaderBinding->bind(
			gltut::RendererBinding::Parameter::VIEWPOINT_PROJECTION_MATRIX,
			"projection");
	}

	gltut::Material* skyboxMaterial = mRenderer.createMaterial();
	GLTUT_CHECK(skyboxMaterial != nullptr, "Failed to create skybox material");
	auto* pass = skyboxMaterial->createPass(
		0,
		mSkyboxShaderBinding,
		1,	// One texture
		0); // No uniform buffers

	GLTUT_CHECK(pass != nullptr, "Failed to create skybox material pass");

	// Set front face culling since we are inside the skybox
	pass->setFaceCulling(FaceCullingMode::FRONT);
	pass->getTextures()->setTexture(&cubemapTexture, 0);

	return skyboxMaterial;
}

/// Updates the shadow factory
void SceneFactoryC::update() noexcept
{
	for (auto& [light, shadowMap] : mShadowMaps)
	{
		shadowMap.update();
	}
}

// End of the namespace gltut
}
