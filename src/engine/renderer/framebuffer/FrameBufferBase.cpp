// Includes
#include "FramebufferBase.h"
#include <iostream>

namespace gltut
{
// Global classes
void FramebufferBase::setColor(Texture* texture) noexcept
{
	// If the texture is not null and is not a color texture, do nothing
	if (texture != nullptr &&
		texture->getFormat() != Texture::Format::RGBA &&
		texture->getFormat() != Texture::Format::RGB)
	{
		std::cerr << "Invalid texture format for color attachment." << std::endl;
		return;
	}
	mColor = texture;
}

void FramebufferBase::setDepth(Texture* texture) noexcept
{
	// If the texture is not null and is not a depth texture, do nothing
	if (texture != nullptr &&
		texture->getFormat() != Texture::Format::FLOAT)
	{
		std::cerr << "Invalid texture format for depth attachment." << std::endl;
		return;
	}
	mDepth = texture;
}

// End of the namespace gltut
}
