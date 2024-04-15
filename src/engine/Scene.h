// Includes
#include <deque>
#include "engine/IScene.h"
#include "Mesh.h"

namespace gltut
{

class Scene final : public IScene
{
public:
	Scene();

	~Scene() noexcept final;

	IMesh* createMesh(
		float* vertices,
		u32 vertexCount,
		u32* indices,
		u32 indexCount) noexcept final;

	void render() noexcept final;

private:
	unsigned mShaderProgram = 0;

	std::deque<Mesh> mMeshes;
};

// End of the namespace gltut
}
