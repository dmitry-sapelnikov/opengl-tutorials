// Includes
#include "TextureFramebufferBase.h"
#include <iostream>

namespace gltut
{
// Global classes
void TextureFramebufferBase::setColor(Texture2* texture) noexcept
{
	// If the texture is not null and is not a color texture, do nothing
	if (texture != nullptr &&
		texture->getFormat() != TextureFormat::RGBA &&
		texture->getFormat() != TextureFormat::RGB)
	{
		std::cerr << "Invalid texture format for color attachment." << std::endl;
		return;
	}
	mColor = texture;
}

void TextureFramebufferBase::setDepth(Texture2* texture) noexcept
{
	// If the texture is not null and is not a depth texture, do nothing
	if (texture != nullptr &&
		texture->getFormat() != TextureFormat::FLOAT)
	{
		std::cerr << "Invalid texture format for depth attachment." << std::endl;
		return;
	}
	mDepth = texture;
}

Point2u TextureFramebufferBase::getSize() const noexcept
{
	if (mColor != nullptr)
	{
		return mColor->getSize();
	}

	if (mDepth != nullptr)
	{
		return mDepth->getSize();
	}
	return Point2u(0, 0);
}

// End of the namespace gltut
}
