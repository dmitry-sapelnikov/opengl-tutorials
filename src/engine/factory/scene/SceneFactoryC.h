#pragma once

// Includes
#include <unordered_map>
#include "engine/factory/scene/SceneFactory.h"
#include "engine/factory/geometry/GeometryFactory.h"
#include "./ShadowMapC.h"


namespace gltut
{

class SceneFactoryC : public SceneFactory, public NonCopyable
{
public:
	/// Constructor
	SceneFactoryC(
		Renderer& renderer,
		GeometryFactory& geometryFactory) noexcept :

		mRenderer(renderer),
		mGeometryFactory(geometryFactory)
	{
	}

	/// Creates a shadow map for the given light
	ShadowMap* createShadowMap(
		const LightNode* light,
		const RenderObject* shadowCaster,
		float frustumSize,
		float frustumNear,
		float frustumFar,
		u32 shadowMapSize) noexcept final;

	/// Creates a skybox for a given cubemap texture and camera
	bool createSkybox(
		const TextureCubemap* cubemapTexture,
		const Viewpoint* viewpoint,
		const Rectangle2u* viewport) noexcept final;

	/// Updates the shadow factory
	void update() noexcept final;

private:
	Material* createSkyboxMaterial(const TextureCubemap& cubemapTexture);

	/// The renderer
	Renderer& mRenderer;

	/// The geometry factory
	GeometryFactory& mGeometryFactory;

	/// The shadow maps
	std::unordered_map<const LightNode*, ShadowMapC> mShadowMaps;

	/// The skybox cube geometry
	Geometry* mSkyboxCube = nullptr;

	/// The skybox shader
	ShaderRendererBinding* mSkyboxShaderBinding = nullptr;
};

// End of the namespace gltut
}
