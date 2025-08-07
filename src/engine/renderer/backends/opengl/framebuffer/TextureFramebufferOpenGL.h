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
		Texture* color,
		Texture* depth);

	/// Destructor
	~TextureFramebufferOpenGL() noexcept final;

	/// Sets the color texture
	void setColor(Texture* texture) noexcept final;

	/// Sets the depth texture
	void setDepth(Texture* texture) noexcept final;

	/// Activates the framebuffer as the current rendering target
	void activate() const noexcept final;

private:
	void validate() const;

	/// Framebuffer ID
	GLuint mId = 0;
};

// End of the namespace gltut
}
