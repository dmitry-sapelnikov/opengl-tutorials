#pragma once

// Includes
#include "engine/graphics/framebuffer/FramebufferManager.h"
#include "../../core/ItemManagerT.h"

namespace gltut
{

/// GraphicsDevice base class
class GraphicsDeviceBase;

/// Implementation of the FramebufferManager interface
class FramebufferManagerC : public ItemManagerT<FramebufferManager>
{
public:
	/// Constructor
	FramebufferManagerC(GraphicsDeviceBase& device) noexcept :
		mDevice(device)
	{
	}

	/// Returns the default (window) framebuffer
	virtual Framebuffer* getDefault() const noexcept final;

	/// Creates a framebuffer
	virtual TextureFramebuffer* create(
		Texture2* color,
		Texture2* depth) noexcept final;

private:
	/// Reference to the graphics device
	GraphicsDeviceBase& mDevice;
};

// End of the namespace gltut
}
