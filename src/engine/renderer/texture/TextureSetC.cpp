// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

// Includes
#include "TextureSetC.h"

namespace gltut
{

// Global classes
const Texture* TextureSetC::getTexture(u32 slot) const noexcept
{
	GLTUT_ASSERT(slot < mTextureSlotsCount);
	return slot < mTextureSlotsCount ? mTextures[slot] : nullptr;
}

void TextureSetC::setTexture(const Texture* texture, u32 slot) noexcept
{
	GLTUT_ASSERT(slot < mTextureSlotsCount);
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
	GLTUT_ASSERT(count <= Texture::TEXTURE_SLOTS);
	mTextureSlotsCount = std::min(count, Texture::TEXTURE_SLOTS);
}

void TextureSetC::bind() const noexcept
{
	for (u32 i = 0; i < mTextureSlotsCount; ++i)
	{
		mDevice.bindTexture(mTextures[i], i);
	}
}

// End of the namespace gltut
}
