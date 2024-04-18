#ifndef OPENGL_TUTORIALS_SCENE_C_H
#define OPENGL_TUTORIALS_SCENE_C_H

// Includes
#include <deque>
#include "engine/core/NonCopyable.h"
#include "engine/Scene.h"
#include "engine/Renderer.h"
#include "MaterialC.h"
#include "MeshC.h"
#include "SceneObjectC.h"

namespace gltut
{
// Global classes
/// Implementation of the Scene interface
class SceneC final : public Scene, public NonCopyable
{
public:
	SceneC(Renderer& renderer);

	Material* createMaterial(Shader* shader) noexcept final;

	Mesh* createMesh(
		VertexFormat vertexFormat,
		float* vertices,
		u32 vertexCount,
		u32* indices,
		u32 indexCount) noexcept final;

	SceneObject* createObject(
		Mesh* mesh,
		Material* material,
		const Matrix4& transform = Matrix4::identity()) noexcept final;

	void render() noexcept final;

private:
	/// The renderer
	Renderer& mRenderer;

	/// The materials
	std::deque<MaterialC> mMaterials;

	/// The meshes
	std::deque<MeshC> mMeshes;

	/// The scene objects
	std::deque<SceneObjectC> mObjects;
};

// End of the namespace gltut
}

#endif
