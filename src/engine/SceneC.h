#ifndef OPENGL_TUTORIALS_SCENE_C_H
#define OPENGL_TUTORIALS_SCENE_C_H

// Includes
#include <deque>
#include "engine/Scene.h"
#include "Meshc.h"

namespace gltut
{

class SceneC final : public Scene
{
public:
	SceneC();

	~SceneC() noexcept final;

	Mesh* createMesh(
		float* vertices,
		u32 vertexCount,
		u32* indices,
		u32 indexCount) noexcept final;

	void render() noexcept final;

private:
	unsigned mShaderProgram = 0;

	std::deque<MeshC> mMeshes;
};

// End of the namespace gltut
}

#endif
