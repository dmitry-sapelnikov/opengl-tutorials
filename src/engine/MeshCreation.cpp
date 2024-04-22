// Includes
#include "engine/MeshCreation.h"

namespace gltut
{

// Global functions
Mesh* createBoxMesh(Scene& scene, float x, float y, float z) noexcept
{
	x *= 0.5f;
	y *= 0.5f;
	z *= 0.5f;

	const float vertices[] =
	{
		// Front
		-x, -y,  z,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
		 x, -y,  z,  0.0f, 0.0f,  1.0f, 1.0f, 0.0f,
		 x,  y,  z,  0.0f, 0.0f,  1.0f, 1.0f, 1.0f,
		-x,  y,  z,  0.0f, 0.0f,  1.0f, 0.0f, 1.0f,

		// Back
		-x, -y, -z,  0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		 x, -y, -z,  0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
		 x,  y, -z,  0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
		-x,  y, -z,  0.0f, 0.0f, -1.0f, 0.0f, 1.0f,

		// Left
		-x, -y, -z, -1.0f, 0.0f,  0.0f, 0.0f, 0.0f,
		-x, -y,  z, -1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
		-x,  y,  z, -1.0f, 0.0f,  0.0f, 1.0f, 1.0f,
		-x,  y, -z, -1.0f, 0.0f,  0.0f, 0.0f, 1.0f,

		// Right
		 x, -y, -z,  1.0f, 0.0f,  0.0f, 0.0f, 0.0f,
		 x, -y,  z,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
		 x,  y,  z,  1.0f, 0.0f,  0.0f, 1.0f, 1.0f,
		 x,  y, -z,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f,

		// Top
		-x,  y, -z,  0.0f, 1.0f,  0.0f, 0.0f, 0.0f,
		 x,  y, -z,  0.0f, 1.0f,  0.0f, 1.0f, 0.0f,
		 x,  y,  z,  0.0f, 1.0f,  0.0f, 1.0f, 1.0f,
		-x,  y,  z,  0.0f, 1.0f,  0.0f, 0.0f, 1.0f,

		// Bottom
		-x, -y, -z,  0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		 x, -y, -z,  0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		 x, -y,  z,  0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
		-x, -y,  z,  0.0f, -1.0f, 0.0f, 0.0f, 1.0f
	};

	u32 indices[] =
	{
		0, 1, 2, 2, 3, 0,
		4, 5, 6, 6, 7, 4,
		8, 9, 10, 10, 11, 8,
		12, 13, 14, 14, 15, 12,
		16, 17, 18, 18, 19, 16,
		20, 21, 22, 22, 23, 20
	};

	return scene.createMesh(VERTEX_FORMAT_POS3_NORM3_TEX2, 24, vertices, 36, indices);
}

// End of the namespace gltut
}
