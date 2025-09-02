// Includes
#include "TextureFactoryC.h"

namespace gltut
{

void TextureFactoryC::createWindowSizeTextureBinding(Texture* texture) noexcept
{
	if (mWindowSizeTextures.contains(texture))
	{
		return;
	}
	mWindowSizeTextures.insert(texture);
	texture->setSize(mWindow.getSize());
}

void TextureFactoryC::removeWindowSizeTextureBinding(Texture* texture) noexcept
{
	mWindowSizeTextures.erase(texture);
}

bool TextureFactoryC::onEvent(const Event& event) noexcept
{
	if (event.type == Event::Type::WINDOW_RESIZE)
	{
		for (Texture* texture : mWindowSizeTextures)
		{
			texture->setSize(event.windowResize.size);
		}
	}
	return false;
}

// End of the namespace gltut
}
