#ifndef OPENGL_TUTORIALS_SCENE_C_H
#define OPENGL_TUTORIALS_SCENE_C_H

// Includes
#include <deque>
#include "engine/core/NonCopyable.h"
#include "engine/Scene.h"
#include "engine/Renderer.h"
#include "Meshc.h"

namespace gltut
{
// Global classes
/// Implementation of the Scene interface
class SceneC final : public Scene, public NonCopyable
{
public:
	SceneC(Renderer& renderer);

	~SceneC() noexcept final;

	Mesh* createMesh(
		VertexFormat vertexFormat,
		float* vertices,
		u32 vertexCount,
		u32* indices,
		u32 indexCount) noexcept final;

	void render() noexcept final;

private:
	/// The renderer
	Renderer& mRenderer;

	/// The default shader
	Shader* mDefaultShader = nullptr;

	/// The meshes
	std::deque<MeshC> mMeshes;
};

// End of the namespace gltut
}

#endif
