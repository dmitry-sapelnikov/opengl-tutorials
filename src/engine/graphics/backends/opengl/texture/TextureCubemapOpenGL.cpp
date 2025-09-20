// Includes
#include "TextureCubemapOpenGL.h"
#include <array>

namespace gltut
{

// Global classes
TextureCubemapOpenGL::TextureCubemapOpenGL(
	const TextureData& minusXData,
	const TextureData& plusXData,
	const TextureData& minusYData,
	const TextureData& plusYData,
	const TextureData& minusZData,
	const TextureData& plusZData,
	const TextureParameters& parameters) :

	TextureTOpenGL<TextureCubemap, GL_TEXTURE_CUBE_MAP>(parameters)
{
	TextureBackupOpenGL backup(GL_TEXTURE_CUBE_MAP);

	glBindTexture(GL_TEXTURE_CUBE_MAP, getId());

	std::array<const TextureData*, 6> faces = {
		&plusXData,
		&minusXData,
		&plusYData,
		&minusYData,
		&plusZData,
		&minusZData};

	for (size_t i = 0; i < faces.size(); ++i)
	{
		const TextureData* faceData = faces[i];
		GLTUT_CHECK(faceData->data != nullptr, "Texture data is null");
		GLTUT_CHECK(faceData->size.x > 0, "Texture width is 0");
		GLTUT_CHECK(faceData->size.y > 0, "Texture height is 0");

		glTexImage2D(
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + static_cast<GLenum>(i),
			0,
			toOpenGLFormat(faceData->format),
			faceData->size.x,
			faceData->size.y,
			0,
			toOpenGLFormat(faceData->format),
			getChannelType(faceData->format),
			faceData->data);
	}
	updateMipmap();
}

// End of the namespace gltut
}
