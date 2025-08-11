#pragma once

// Includes
#include "engine/graphics/texture/Texture.h"
#include "engine/renderer/viewpoint/Viewpoint.h"
#include "engine/renderer/objects/RenderObject.h"
#include "engine/scene/nodes/LightNode.h"

namespace gltut
{

class ShadowFactory
{
public:
	/// Virtual destructor
	virtual ~ShadowFactory() noexcept = default;

	/// Creates a texture-to-window render pass
	virtual ShadowMap* createShadowMap(
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
