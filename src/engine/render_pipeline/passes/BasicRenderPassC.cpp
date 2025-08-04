// Includes
#include "BasicRenderPassC.h"

namespace gltut
{

//	Global classes
void BasicRenderPassC::addGeometry(Mesh* geometry, Shader* shader) noexcept
{
	GLTUT_CATCH_ALL_BEGIN
		mGeometries.emplace_back(geometry, shader);
	GLTUT_CATCH_ALL_END("Failed to add geometry to the render pass")
}

void BasicRenderPassC::doExecute() noexcept
{
	for (const auto& [mesh, shader] : mGeometries)
	{
		if (mesh != nullptr && shader != nullptr)
		{
			shader->activate();
			mesh->render();
		}
	}
}

// End of the namespace gltut
}
