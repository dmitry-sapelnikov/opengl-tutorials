#pragma once

// Includes
#include <glad/glad.h>
#include "../../../framebuffer/TextureFramebufferBase.h"

namespace gltut
{

class TextureFramebufferOpenGL final : public TextureFramebufferBase
{
public:
	/**
		Constructor
		\throw std::runtime_error If the framebuffer could not be created
	*/
	TextureFramebufferOpenGL(
		Texture2* color,
		Texture2* depth);

	/// Destructor
	~TextureFramebufferOpenGL() noexcept final;

	/// Sets the color texture
	void setColor(Texture2* texture) noexcept final;

	/// Sets the depth texture
	void setDepth(Texture2* texture) noexcept final;

	/// Binds the framebuffer as the current rendering target
	void bind() const noexcept final;

private:
	/// Sets the color texture without validation
	void doSetColor(Texture2* texture) noexcept;

	/// Sets the depth texture without validation
	void doSetDepth(Texture2* texture) noexcept;

	/// Checks if the framebuffer is valid
	bool isValid() const noexcept;

	/// Framebuffer ID
	GLuint mId = 0;
};

// End of the namespace gltut
}
