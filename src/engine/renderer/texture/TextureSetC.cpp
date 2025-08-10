// Includes
#include "TextureSetC.h"

namespace gltut
{

// Global classes
const Texture* TextureSetC::getTexture(u32 slot) const noexcept
{
	return slot < mTextureSlotsCount ? mTextures[slot] : nullptr;
}

void TextureSetC::setTexture(const Texture* texture, u32 slot) noexcept
{
	if (slot < mTextureSlotsCount)
	{
		mTextures[slot] = texture;
	}
}

u32 TextureSetC::getTextureSlotsCount() const noexcept
{
	return mTextureSlotsCount;
}

void TextureSetC::setTextureSlotsCount(u32 count) noexcept
{
	mTextureSlotsCount = std::min(count, Texture::TEXTURE_SLOTS);
}

void TextureSetC::bind() const noexcept
{
	for (u32 i = 0; i < mTextureSlotsCount; ++i)
	{
		if (mTextures[i] != nullptr)
		{
			mTextures[i]->bind(i);
		}
	}
}

// End of the namespace gltut
}
