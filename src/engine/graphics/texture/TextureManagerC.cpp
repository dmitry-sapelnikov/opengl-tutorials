// Includes
#include "TextureManagerC.h"
#include <array>
#include <string>
#include "./stb_image.h"
#include "../GraphicsDeviceBase.h"

namespace gltut
{

// Local functions
namespace
{

// Inverts a specific channel in the image data
void invertChannel(
	unsigned char* data,
	u32 pixelCount,
	u32 channelIndex,
	u32 channelCount) noexcept
{
	GLTUT_ASSERT(data != nullptr);
	GLTUT_ASSERT(channelIndex < channelCount);

	for (u32 i = 0; i < pixelCount; ++i)
	{
		data[i * channelCount + channelIndex] = 255 - data[i * channelCount + channelIndex];
	}
}

TextureData loadImage(
	const char* imagePath,
	const TextureManager::LoadParameters& parameters)
{
	stbi_set_flip_vertically_on_load(true);
	int width = 0;
	int height = 0;
	int channels = 0;
	unsigned char* data = stbi_load(imagePath, &width, &height, &channels, 0);

	GLTUT_CHECK(data != nullptr, "Failed to load image");
	GLTUT_CHECK(width > 0, "Image width <= 0");
	GLTUT_CHECK(height > 0, "Image height <= 0");
	GLTUT_CHECK(
		channels == 1 || channels == 3 || channels == 4,
		("Unsupported number of channels: " + std::to_string(channels)).c_str());

	TextureFormat format;
	switch (channels)
	{
	case 1:
		format = TextureFormat::R;
		break;

	case 3:
		format = TextureFormat::RGB;
		break;

	case 4:
		format = TextureFormat::RGBA;
		break;

		GLTUT_UNEXPECTED_SWITCH_DEFAULT_CASE(channels)
	}

	for (u32 i = 0; i < static_cast<u32>(channels); ++i)
	{
		if (parameters.invertChannel[i])
		{
			invertChannel(
				data,
				static_cast<u32>(width * height),
				i,
				static_cast<u32>(channels));
		}
	}

	return { data, { static_cast<u32>(width), static_cast<u32>(height) }, format };
}


// End of the anonymous namespace
}

// Global classes
Texture2* TextureManagerC::create(
	const TextureData& data,
	const TextureParameters& parameters) noexcept
{
	Texture2* result = nullptr;
	GLTUT_CATCH_ALL_BEGIN
		result = static_cast<Texture2*>(add(
			mDevice.createBackendTexture2(data, parameters)));
	GLTUT_CATCH_ALL_END("Failed to create texture")
		return result;
}

Texture2* TextureManagerC::load(
	const char* imagePath,
	const TextureParameters& textureParameters,
	const LoadParameters& loadParameters) noexcept
{
	Texture2* result = nullptr;
	TextureData textureData;

	GLTUT_CATCH_ALL_BEGIN
		textureData = loadImage(imagePath, loadParameters);
	result = create(textureData, textureParameters);
	GLTUT_CATCH_ALL_END("Failed to load texture from file: " + std::string(imagePath))

		stbi_image_free(const_cast<u8*>(textureData.data));
	return result;
}

TextureCubemap* TextureManagerC::load(
	const char* plusXAxisImagePath,
	const char* minusXAxisImagePath,
	const char* plusYAxisImagePath,
	const char* minusYAxisImagePath,
	const char* plusZAxisImagePath,
	const char* minusZAxisImagePath,
	const TextureParameters& textureParameters,
	const LoadParameters& loadParameters) noexcept
{
	TextureCubemap* result = nullptr;
	try
	{
		const std::array<const char*, 6> paths = {
			plusXAxisImagePath,
			minusXAxisImagePath,
			plusYAxisImagePath,
			minusYAxisImagePath,
			plusZAxisImagePath,
			minusZAxisImagePath,
		};

		std::array<TextureData, 6> textureData;

		for (u32 i = 0; i < paths.size(); ++i)
		{
			textureData[i] = loadImage(paths[i], loadParameters);
		}

		result = static_cast<TextureCubemap*>(add(
			mDevice.createBackendTextureCubemap(
				textureData[0],
				textureData[1],
				textureData[2],
				textureData[3],
				textureData[4],
				textureData[5],
				textureParameters)));
	}
	GLTUT_CATCH_ALL("Failed to load cubemap texture")
	return result;
}

const Texture2* TextureManagerC::createSolidColor(const Color& color) noexcept
{
	const u8 r8 = static_cast<u8>(std::clamp(color.r, 0.0f, 1.0f) * 255);
	const u8 g8 = static_cast<u8>(std::clamp(color.g, 0.0f, 1.0f) * 255);
	const u8 b8 = static_cast<u8>(std::clamp(color.b, 0.0f, 1.0f) * 255);
	const u8 a8 = static_cast<u8>(std::clamp(color.a, 0.0f, 1.0f) * 255);
	const u32 color_hex = ((u32)r8 << 24) | ((u32)g8 << 16) | ((u32)b8 << 8) | (u32)a8;

	Texture2* result = nullptr;
	GLTUT_CATCH_ALL_BEGIN
		if (auto findResult = mSolidColorTextures.find(color_hex);
			findResult != mSolidColorTextures.end())
	{
		return findResult->second;
	}

	const u8 colorData[] = { r8, g8, b8, a8 };
	result = create(
		{ colorData, {1, 1}, TextureFormat::RGBA },
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
