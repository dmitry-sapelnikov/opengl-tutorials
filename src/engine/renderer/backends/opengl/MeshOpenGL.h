#ifndef OPENGL_TUTORIALS_MESH_OPEN_GL_H
#define OPENGL_TUTORIALS_MESH_OPEN_GL_H

// Includes
#include <glad/glad.h>
#include "engine/core/NonCopyable.h"
#include "engine/renderer/mesh/Mesh.h"

namespace gltut
{

class MeshOpenGL final : public Mesh, public NonCopyable
{
public:
	/// Constructor
	MeshOpenGL(
		VertexFormat vertexFormat,
		u32 vertexCount,
		const float* vertices,
		u32 indexCount,
		const u32* indices);

	/// Destructor
	~MeshOpenGL() final;

	/// Renders the mesh
	void render() const noexcept final;

private:
	/// Indices count
	GLsizei mIndexCount;

	/// The vertex buffer object
	GLuint mVertexBuffer = 0;

	/// The element buffer object
	GLuint mIndexBuffer = 0;

	/// The vertex array object
	GLuint mVertexArray = 0;
};

// End of the namespace gltut
}

#endif
