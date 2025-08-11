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
	void* data = nullptr;
	Texture* result = nullptr;
	GLTUT_CATCH_ALL_BEGIN
		stbi_set_flip_vertically_on_load(true);
		int width = 0;
		int height = 0;
		int channels = 0;
		void* data = stbi_load(imagePath, &width, &height, &channels, 0);
		GLTUT_CHECK(data != nullptr, "Failed to load image");
		GLTUT_CHECK(width > 0, "Image width <= 0");
		GLTUT_CHECK(height > 0, "Image height <= 0");
		GLTUT_CHECK(
			channels == 3 || channels == 4,
			("Unsupported number of channels: " + std::to_string(channels)).c_str());

		result = create(
			data,
			{ static_cast<u32>(width), static_cast<u32>(height) },
			channels == 3 ? TextureFormat::RGB : TextureFormat::RGBA,
			parameters);
	GLTUT_CATCH_ALL_END("Failed to load texture from file: " + std::string(imagePath))

	stbi_image_free(data);
	return result;
}

const Texture* TextureManagerC::createSolidColor(const Color& color) noexcept
{
	const u8 r8 = static_cast<u8>(std::clamp(color.r, 0.0f, 1.0f) * 255);
	const u8 g8 = static_cast<u8>(std::clamp(color.g, 0.0f, 1.0f) * 255);
	const u8 b8 = static_cast<u8>(std::clamp(color.b, 0.0f, 1.0f) * 255);
	const u8 a8 = static_cast<u8>(std::clamp(color.a, 0.0f, 1.0f) * 255);
	const u32 color_hex = ((u32)r8 << 24) | ((u32)g8 << 16) | ((u32)b8 << 8) | (u32)a8;

	Texture* result = nullptr;
	GLTUT_CATCH_ALL_BEGIN
		if (auto findResult = mSolidColorTextures.find(color_hex);
			findResult != mSolidColorTextures.end())
		{
			return findResult->second;
		}

		const u8 colorData[] = { r8, g8, b8, a8 };
		result = create(
			colorData,
			{ 1, 1 },
			TextureFormat::RGBA,
			{ TextureFilterMode::NEAREST,
			TextureFilterMode::NEAREST,
			TextureWrapMode::CLAMP_TO_EDGE });

		if (result != nullptr)
		{
			mSolidColorTextures[color_hex] = result;
		}
	GLTUT_CATCH_ALL_END("Failed to create solid color texture")
	return result;
}

// End of the namespace gltut
}
