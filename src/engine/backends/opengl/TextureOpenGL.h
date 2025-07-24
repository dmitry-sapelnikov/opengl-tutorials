#ifndef OPENGL_TUTORIALS_TEXTURE_OPEN_GL_H
#define OPENGL_TUTORIALS_TEXTURE_OPEN_GL_H

// Includes
#include <string>
#include "engine/core/NonCopyable.h"
#include "engine/core/Types.h"
#include "engine/texture/Texture.h"

namespace gltut
{

class TextureOpenGL final : public Texture, public NonCopyable
{
public:
	/**
		Constructor
		\throw std::runtime_error If the shader could not be created
	*/
	TextureOpenGL(
		const u8* data,
		u32 width,
		u32 height,
		u32 dataChannelsCount);

	/// Destructor
	~TextureOpenGL() noexcept final;

	/// Returns the wrap mode of the texture
	WrapMode getWrapMode() const noexcept final;

	/// Sets the wrap mode of the texture
	void setWrapMode(WrapMode mode) noexcept final;

	/// Binds the texture
	void bind(u32 slot) const noexcept final;

private:
	/// Texture ID
	unsigned mTexture = 0;

	/// Wrap mode
	WrapMode mWrapMode = WrapMode::REPEAT;
};

// End of the namespace gltut
}

#endif
