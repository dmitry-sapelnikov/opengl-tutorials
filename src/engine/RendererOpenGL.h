#ifndef OPENGL_TUTORIALS_RENDERER_OPEN_GL_H
#define OPENGL_TUTORIALS_RENDERER_OPEN_GL_H

// Includes
#include "engine/core/NonCopyable.h"
#include "RendererBase.h"
#include <vector>
#include <memory>
#include <glad/glad.h>

namespace gltut
{
/// OpenGL renderer
class RendererOpenGL final : public RendererBase
{
public:
	/// Constructor
	RendererOpenGL();

	/// Sets the clear color
	void setClearColor(float r, float g, float b, float a) noexcept final;

	/// Clears the screen
	void clear() noexcept final;

	/// Adds a mesh
	u32 addMesh(const Mesh& mesh) noexcept final;

	/// Removes a mesh
	void removeMesh(u32 index) noexcept final;

	/// Renders a mesh
	void renderMesh(u32 index) const noexcept final;

	/// Creates a shader
	Shader* createShader(
		const char* vertexShader,
		const char* fragmentShader) noexcept final;

	/// Loads a shader from files
	Shader* loadShader(
		const char* vertexShaderPath,
		const char* fragmentShaderPath) noexcept final;

	/// Removes a shader
	void removeShader(Shader* shader) noexcept final;

	/// Creates a texture
	Texture* createTexture(
		const u8* data,
		u32 width,
		u32 height,
		u32 channels) noexcept final;

	/// Removes a texture
	void removeTexture(Texture* texture) noexcept final;

private:
	struct MeshBuffers
	{
		/// The vertex buffer object
		GLuint vertexBuffer;

		/// The element buffer object
		GLuint indexBuffer;

		/// Number of indices
		u32 indicesCount;

		/// The vertex array object
		GLuint vao;

		MeshBuffers() noexcept
		{
			reset();
		}

		MeshBuffers(
			GLuint vertexBuffer,
			GLuint indexBuffer,
			u32 indicesCount,
			GLuint vao) :

			vertexBuffer(vertexBuffer),
			indexBuffer(indexBuffer),
			indicesCount(indicesCount),
			vao(vao)
		{
			GLTUT_CHECK(isValid(), "Invalid mesh buffers");
		}

		bool isValid() const noexcept
		{
			return 
				vertexBuffer != 0 && 
				indexBuffer != 0 &&
				vao != 0 &&
				indicesCount != 0;
		}

		void reset() noexcept
		{
			vertexBuffer = 0;
			indexBuffer = 0;
			indicesCount = 0;
			vao = 0;
		}
	};

	/// Allocates a vertex buffer
	GLuint allocateVertexBuffer(float* vertices, u32 count) noexcept;

	/// Allocates an index buffer
	GLuint allocateIndexBuffer(u32* indices, u32 count) noexcept;

	/// Allocates a vertex array
	GLuint allocateVertexArray(
		VertexFormat vertexFormat,
		GLuint vertexBuffer,
		GLuint indexBuffer) noexcept;

	/// Shaders
	std::vector<std::unique_ptr<Shader>> mShaders;

	/// Textures
	std::vector<std::unique_ptr<Texture>> mTextures;

	/// Free mesh indices
	std::vector<u32> mFreeMeshIndices;

	/// Buffers for meshes
	std::vector<MeshBuffers> mMeshBuffers;
};

// End of the namespace gltut
}

#endif
