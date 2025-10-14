// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

// Includes
#include "TextureFactoryC.h"

namespace gltut
{

bool TextureFactoryC::createWindowSizeTextureBinding(Texture2* texture) noexcept
{
	try
	{
		if (!mWindowSizeTextures.contains(texture))
		{
			mWindowSizeTextures.insert(texture);
			texture->setSize(mWindow.getSize());
		}
		return true;
	}
	GLTUT_CATCH_ALL("TextureFactoryC::createWindowSizeTextureBinding failed")
	return false;
}

bool TextureFactoryC::removeWindowSizeTextureBinding(Texture2* texture) noexcept
{
	try
	{
		mWindowSizeTextures.erase(texture);
		return true;
	}
	GLTUT_CATCH_ALL("TextureFactoryC::removeWindowSizeTextureBinding failed");
	return false;
}

Texture2* TextureFactoryC::createWindowSizeTexture(TextureFormat format) noexcept
{
	Texture2* colorTexture = mGraphicsDevice.getTextures()->create(
		{nullptr,
		 mWindow.getSize(),
		 format},
		{TextureFilterMode::NEAREST,
		 TextureFilterMode::NEAREST,
		 TextureWrapMode::CLAMP_TO_EDGE});

	if (colorTexture == nullptr)
	{
		return nullptr;
	}

	if (bool bindingCreated = createWindowSizeTextureBinding(colorTexture);
		!bindingCreated)
	{
		mGraphicsDevice.getTextures()->remove(colorTexture);
		return nullptr;
	}
	return colorTexture;
}

bool TextureFactoryC::onEvent(const Event& event) noexcept
{
	if (event.type == Event::Type::WINDOW_RESIZE)
	{
		for (Texture2* texture : mWindowSizeTextures)
		{
			texture->setSize(event.windowResize.size);
		}
	}
	return false;
}

// End of the namespace gltut
}
