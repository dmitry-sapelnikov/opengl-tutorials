// Includes
#include "TextureManagerC.h"
#include <string>
#include "./stb_image.h"
#include "../GraphicsDeviceBase.h"

namespace gltut
{

// Global classes
Texture* TextureManagerC::create(
	const void* data,
	const Point2u& size,
	TextureFormat format,
	const TextureParameters& parameters) noexcept
{
	Texture* result = nullptr;
	GLTUT_CATCH_ALL_BEGIN
		result = add(mDevice.createBackendTexture(
			data,
			size,
			format,
			parameters));
	GLTUT_CATCH_ALL_END("Failed to create texture")
		return result;
}

Texture* TextureManagerC::load(
	const char* imagePath,
	const TextureParameters& parameters) noexcept
{
	stbi_set_flip_vertically_on_load(true);
	int width = 0;
	int height = 0;
	int channels = 0;
	void* data = stbi_load(imagePath, &width, &height, &channels, 0);
	if (data == nullptr)
	{
		std::cerr << "Failed to load the image: " << imagePath << std::endl;
		stbi_image_free(data);
		return nullptr;
	}

	if (channels != 3 && channels != 4)
	{
		std::cerr << "Unsupported image format in: " << imagePath << std::endl;
		stbi_image_free(data);
		return nullptr;
	}

	Texture* result = create(
		data,
		{ static_cast<u32>(width), static_cast<u32>(height) },
		channels == 3 ? TextureFormat::RGB : TextureFormat::RGBA,
		parameters);

	stbi_image_free(data);
	return result;
}

// End of the namespace gltut
}
