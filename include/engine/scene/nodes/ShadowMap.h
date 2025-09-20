#pragma once

// Includes
#include "engine/graphics/texture/Texture.h"
#include "engine/renderer/viewpoint/Viewpoint.h"

namespace gltut
{
// Global classes
/// Contains the colors used for a light source
class ShadowMap
{
public:
	/// Virtual constructor
	virtual ~ShadowMap() noexcept = default;

	/// Returns the shadow map texture
	virtual const Texture* getTexture() const noexcept = 0;

	/// Returns the shadow map viewpoint
	virtual const Viewpoint* getViewpoint() const noexcept = 0;

	/// Returns the near clipping plane of the shadow map
	virtual float getFrustumNear() const noexcept = 0;

	/// Returns the far clipping plane of the shadow map
	virtual float getFrustumFar() const noexcept = 0;

	/// Returns view-projection matrix for the shadow map
	virtual Matrix4 getShadowMatrix() const noexcept = 0;

	/// Updates the shadow map
	virtual void update() noexcept = 0;
};

// End of the namespace gltut
}
