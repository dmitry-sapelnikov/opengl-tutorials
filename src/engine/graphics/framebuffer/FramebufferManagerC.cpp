// Includes
#include "FramebufferManagerC.h"
#include <string>
#include "../GraphicsDeviceBase.h"

namespace gltut
{

// Global classes
Framebuffer* FramebufferManagerC::getDefault() const noexcept
{
	return mDevice.getDefaultFramebuffer();
}

TextureFramebuffer* FramebufferManagerC::create(
	Texture* color,
	Texture* depth) noexcept
{
	TextureFramebuffer* result = nullptr;
	GLTUT_CATCH_ALL_BEGIN
		result = add(mDevice.createBackendTextureFramebuffer(
			color,
			depth));
	GLTUT_CATCH_ALL_END("Failed to create framebuffer")
	return result;
}

// End of the namespace gltut
}
