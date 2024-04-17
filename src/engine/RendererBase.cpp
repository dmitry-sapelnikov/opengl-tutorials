// Includes
#include "RendererBase.h"
#include <iostream>
#include "stb_image.h"

namespace gltut
{

Texture* RendererBase::loadTexture(const char* imagePath) noexcept
{
	stbi_set_flip_vertically_on_load(true);
	int width = 0;
	int height = 0;
	int channels = 0;
	unsigned char* data = stbi_load(imagePath, &width, &height, &channels, 0);
	if (data == nullptr)
	{
		std::cerr << "Failed to load the image: " << imagePath << std::endl;
		return nullptr;
	}
	Texture* result = createTexture(data, width, height, channels);
	stbi_image_free(data);
	return result;
}

// End of the namespace gltut
}
