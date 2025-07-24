// Includes
#include "RendererBase.h"
#include <iostream>
#include "./texture/stb_image.h"

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

Texture* RendererBase::createSolidColorTexture(
	float r,
	float g,
	float b,
	float a) noexcept
{
	const u8 r8 = static_cast<u8>(r * 255);
	const u8 g8 = static_cast<u8>(g * 255);
	const u8 b8 = static_cast<u8>(b * 255);
	const u8 a8 = static_cast<u8>(a * 255);
	const u32 color_hex = ((u32)r8 << 24) | ((u32)g8 << 16) | ((u32)b8 << 8) | (u32)a8;

	Texture* result = nullptr;
	GLTUT_CATCH_ALL_BEGIN
		if (auto findResult = mSolidColorTextures.find(color_hex);
			findResult != mSolidColorTextures.end())
		{
			return findResult->second;
		}

		const u8 colorData[] = { r8, g8, b8, a8 };
		result = createTexture(colorData, 1U, 1U, 4U);
		if (result != nullptr)
		{
			mSolidColorTextures[color_hex] = result;
		}
	GLTUT_CATCH_ALL_END("Failed to create solid color texture")
	
	return result;
}

void RendererBase::onEvent(const Event& event) noexcept
{
	if (event.type == Event::Type::WINDOW_RESIZE)
	{
		clear();
		onResize(event.windowResize.size);
	}
}

// End of the namespace gltut
}
