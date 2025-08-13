#pragma once

// Includes
#include "engine/core/Types.h"
#include "engine/core/ItemManager.h"
#include "engine/math/Color.h"
#include "engine/math/Rectangle.h"
#include "engine/graphics/geometry/Geometry.h"
#include "engine/graphics/shader/Shader.h"

#include "engine/graphics/geometry/GeometryManager.h"
#include "engine/graphics/framebuffer/FramebufferManager.h"
#include "engine/graphics/shader/ShaderManager.h"
#include "engine/graphics/texture/TextureManager.h"


#include "engine/graphics/framebuffer/TextureFramebuffer.h"

namespace gltut
{
//	Global classes
///	The graphics device
class GraphicsDevice
{
public:
	/// Virtual destructor
	virtual ~GraphicsDevice() noexcept = default;

	/// Clears the current render target
	virtual void clear(
		const Color* color,
		bool depth) noexcept = 0;

	/// Returns the geometry manager
	virtual GeometryManager* getGeometries() = 0;

	/// Returns the framebuffer manager
	virtual FramebufferManager* getFramebuffers() = 0;

	/// Return the shader manager
	virtual ShaderManager* getShaders() = 0;

	/// Returns the texture manager
	virtual TextureManager* getTextures() = 0;

	/// Binds a texture to a slot
	virtual void bindTexture(const Texture* texture, u32 slot) noexcept = 0;

	/// Binds a framebuffer
	virtual void bindFramebuffer(
		Framebuffer* frameBuffer,
		Rectangle2u* viewport) noexcept = 0;

	/// Enables or disables vertical synchronization
	virtual void enableVSync(bool vSync) noexcept = 0;

	/// Sets face cull
	virtual void setFaceCulling(bool back, bool front) noexcept = 0;
};

// End of the namespace gltut
}
