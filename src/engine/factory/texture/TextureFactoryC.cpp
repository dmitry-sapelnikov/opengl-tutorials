// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

// Includes
#include "TextureFactoryC.h"

namespace gltut
{

void TextureFactoryC::createWindowSizeTextureBinding(Texture2* texture) noexcept
{
	if (mWindowSizeTextures.contains(texture))
	{
		return;
	}
	mWindowSizeTextures.insert(texture);
	texture->setSize(mWindow.getSize());
}

void TextureFactoryC::removeWindowSizeTextureBinding(Texture2* texture) noexcept
{
	mWindowSizeTextures.erase(texture);
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
