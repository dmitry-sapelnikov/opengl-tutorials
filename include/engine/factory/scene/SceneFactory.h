#pragma once

// Includes
#include "engine/graphics/texture/TextureCubemap.h"
#include "engine/math/Rectangle.h"
#include "engine/renderer/objects/RenderObject.h"
#include "engine/renderer/viewpoint/Viewpoint.h"
#include "engine/scene/nodes/LightNode.h"

namespace gltut
{
// Global classes

/// The scene factory interface. Creates various scene elements.
class SceneFactory
{
public:
	/// Virtual destructor
	virtual ~SceneFactory() noexcept = default;

	/// Creates a texture-to-window render pass
	virtual ShadowMap* createShadowMap(
		const LightNode* light,
		const RenderObject* shadowCaster,
		float frustumSize,
		float frustumNear,
		float frustumFar,
		u32 shadowMapSize) noexcept = 0;

	/// Creates a skybox for a given cubemap texture and camera
	virtual bool createSkybox(
		const TextureCubemap* cubemapTexture,
		const Viewpoint* viewpoint,
		const Rectangle2u* viewport) noexcept = 0;

	/// Updates the factory
	virtual void update() noexcept = 0;
};

// End of the namespace gltut
}
