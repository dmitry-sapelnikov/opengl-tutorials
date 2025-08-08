#pragma once

// Includes
#include "engine/renderer/Texture.h"
#include "engine/render_pipeline/viewpoint/Viewpoint.h"
#include "engine/render_pipeline/objects/RenderObject.h"
#include "engine/scene/nodes/LightNode.h"

namespace gltut
{

class ShadowFactory
{
public:
	/// Virtual destructor
	virtual ~ShadowFactory() noexcept = default;

	/// Creates a texture-to-window render pass
	virtual std::pair<const Viewpoint*, const Texture*>createShadowMap(
		const LightNode* light,
		const RenderObject* shadowCaster,
		float frustumSize,
		float frustumNear,
		float frustumFar,
		u32 shadowMapSize) noexcept = 0;

	/// Updates the factory
	virtual void update() noexcept = 0;
};

// End of the namespace gltut
}
