// Includes
#include "Texture2OpenGL.h"

namespace gltut
{

// Global classes
Texture2OpenGL::Texture2OpenGL(
	const TextureData& data,
	const TextureParameters& parameters) :

	TextureTOpenGL<Texture2, GL_TEXTURE_2D>(parameters),
	mSize(data.size),
	mFormat(data.format)
{
	GLTUT_CHECK(data.size.x > 0, "Texture width is 0");
	GLTUT_CHECK(data.size.y > 0, "Texture height is 0");
	create(data.data);
}

void Texture2OpenGL::setSize(const Point2u& size) noexcept
{
	GLTUT_ASSERT(size.x > 0);
	GLTUT_ASSERT(size.y > 0);

	if (size.x == 0 ||
		size.y == 0 ||
		size.x == mSize.x && size.y == mSize.y)
	{
		return;
	}

	mSize = size;
	create(nullptr);
}

void Texture2OpenGL::create(const void* data) noexcept
{
	// Get the currently bound texture to restore it after
	TextureBackupOpenGL backup(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, getId());

	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		toOpenGLFormat(getFormat()),
		mSize.x,
		mSize.y,
		0,
		toOpenGLFormat(getFormat()),
		getChannelType(getFormat()),
		data);

	updateMipmap();
}

// End of the namespace gltut
}
