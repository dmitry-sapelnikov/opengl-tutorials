#ifndef OPENGL_TUTORIALS_SCENE_C_H
#define OPENGL_TUTORIALS_SCENE_C_H

// Includes
#include <deque>
#include "engine/core/NonCopyable.h"
#include "engine/Scene.h"
#include "RendererBase.h"
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
	SceneC(RendererBase& renderer);

	Material* createMaterial(Shader* shader) noexcept final;

	Mesh* createMesh(
		VertexFormat vertexFormat,
		u32 vertexCount,
		float* vertexData,
		u32 indexCount,
		u32* indexData) noexcept final;

	SceneObject* createObject(
		Mesh* mesh,
		Material* material,
		const Matrix4& transform = Matrix4::identity()) noexcept final;

	void render() noexcept final;

private:
	/// The renderer
	RendererBase& mRenderer;

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
