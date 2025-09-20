// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

#pragma once

// Includes
#include "../../core/ItemManagerT.h"
#include "engine/core/ItemManager.h"
#include "engine/graphics/texture/TextureManager.h"
#include <unordered_map>

namespace gltut
{

/// GraphicsDevice base class
class GraphicsDeviceBase;

/// Implementation of the TextureManager interface
class TextureManagerC : public ItemManagerT<TextureManager>
{
public:
	/// Constructor
	TextureManagerC(GraphicsDeviceBase& device) noexcept :
		mDevice(device)
	{
	}

	/// Creates a 2D texture from raw data
	Texture2* create(
		const TextureData& data,
		const TextureParameters& parameters) noexcept final;

	/// Loads a 2D texture from an image file
	Texture2* load(
		const char* imagePath,
		const TextureParameters& textureParameters,
		const LoadParameters& loadParameters) noexcept final;

	/// Loads a cubemap texture from 6 image files
	TextureCubemap* load(
		const char* plusXAxisImagePath,
		const char* minusXAxisImagePath,
		const char* plusYAxisImagePath,
		const char* minusYAxisImagePath,
		const char* plusZAxisImagePath,
		const char* minusZAxisImagePath,
		const TextureParameters& textureParameters,
		const LoadParameters& loadParameters) noexcept final;

	/// Creates a solid color texture
	const Texture2* createSolidColor(const Color& color) noexcept final;

private:
	/// Reference to the graphics device
	GraphicsDeviceBase& mDevice;

	/// Solid color textures
	std::unordered_map<u32, const Texture2*> mSolidColorTextures;
};

// End of the namespace gltut
}
