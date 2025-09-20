#pragma once

namespace gltut
{
// Global enums
/// Texture filter modes
enum class TextureFilterMode
{
	NEAREST,
	LINEAR,
	NEAREST_MIPMAP_NEAREST,
	LINEAR_MIPMAP
};

/// Texture wrap modes
enum class TextureWrapMode
{
	REPEAT,
	CLAMP_TO_EDGE
};

// Global classes
/// Represents texture parameters
struct TextureParameters
{
	/// The minification filter mode
	TextureFilterMode minFilter;

	/// The magnification filter mode
	TextureFilterMode magFilter;

	/// The wrap mode for the texture
	TextureWrapMode wrapMode;

	/// Constructor
	TextureParameters(
		TextureFilterMode minFilter = TextureFilterMode::LINEAR_MIPMAP,
		TextureFilterMode magFilter = TextureFilterMode::LINEAR,
		TextureWrapMode wrapMode = TextureWrapMode::REPEAT) noexcept :
		minFilter(minFilter),
		magFilter(magFilter),
		wrapMode(wrapMode)
	{
	}
};

// End of the namespace gltut
}
