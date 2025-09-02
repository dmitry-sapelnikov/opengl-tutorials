#pragma once

// Includes
#include "engine/graphics/texture/Texture2.h"

namespace gltut
{
// Global classes
/// The texture factory interface. Creates various textures
class TextureFactory
{
public:
	/// Virtual destructor
	virtual ~TextureFactory() noexcept = default;

	/// Creates a binding between a texture and the window size
	virtual void createWindowSizeTextureBinding(Texture2* texture) noexcept = 0;

	/// Removes the window-size texture binding for a texture
	virtual void removeWindowSizeTextureBinding(Texture2* texture) noexcept = 0;
};

// End of the namespace gltut
}
