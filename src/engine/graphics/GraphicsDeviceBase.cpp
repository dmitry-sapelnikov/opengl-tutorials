// Includes
#include "GraphicsDeviceBase.h"

#include <iostream>
#include "../core/File.h"

namespace gltut
{

GraphicsDeviceBase::GraphicsDeviceBase(Window& window) noexcept :
	mWindow(window),
	mGeometries(*this),
	mFramebuffers(*this),
	mShaders(*this),
	mShaderUniformBuffers(*this),
	mTextures(*this)
{
}

void GraphicsDeviceBase::bindFramebuffer(
	Framebuffer* framebuffer,
	Rectangle2u* viewport) noexcept
{
	if (framebuffer == nullptr)
	{
		return;
	}

	framebuffer->bind();
	if (viewport != nullptr)
	{
		setViewport(*viewport);
	}
	else
	{
		// If no viewport is provided, use the framebuffer size
		setViewport({ { 0, 0 }, framebuffer->getSize() });
	}
}

// End of the namespace gltut
}
