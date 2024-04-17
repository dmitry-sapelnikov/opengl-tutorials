#ifndef OPENGL_TUTORIALS_MESH_C_H
#define OPENGL_TUTORIALS_MESH_C_H

// Includes
#include "engine/Mesh.h"
#include "engine/Renderer.h"
#include "engine/core/NonCopyable.h"
#include <array>
#include <vector>

namespace gltut
{

class MeshC final : public Mesh, public NonCopyable
{
public:
	/// Constructor
	MeshC(
		Renderer& renderer,
		VertexFormat vertexFormat,
		float* vertices,
		u32 vertexCount,
		u32* indices,
		u32 indexCount);

	/// Destructor
	~MeshC() final;

	/// Renders the mesh
	void render() const noexcept final;

	///	Returns the shader
	Shader* getShader() const noexcept final;

	/// Sets a shader
	void setShader(Shader* shader) noexcept final;

	/// Sets a texture
	void setTexture(Texture* texture, u32 slot) noexcept final;

private:
	static constexpr u32 TEXTURE_SLOTS = 16;

	/// The renderer
	Renderer& mRenderer;

	/// The vertices
	std::vector<float> mVertices;

	/// The indices
	std::vector<u32> mIndices;

	/// The vertex buffer object
	unsigned mVBO = 0;

	/// The vertex array object
	unsigned mVAO = 0;

	/// The element buffer object
	unsigned mEBO = 0;

	/// The shader
	Shader* mShader = nullptr;

	/// Texture slots
	std::array<Texture*, TEXTURE_SLOTS> mTextures;
};

// End of the namespace gltut
}

#endif
