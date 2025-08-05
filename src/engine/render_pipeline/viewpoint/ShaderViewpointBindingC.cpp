// Includes
#include "ShaderViewpointBindingC.h"

namespace gltut
{
// Global classes
void ShaderViewpointBindingC::update(const Viewpoint* viewpoint) const noexcept
{
	Shader* shader = getShader();

	if (shader == nullptr || viewpoint == nullptr)
	{
		return;
	}

	if (const char* cameraView = getBoundShaderParameter(Parameter::VIEW_MATRIX);
		cameraView != nullptr)
	{
		shader->setMat4(cameraView, viewpoint->getViewMatrix().data());
	}

	if (const char* cameraProjection = getBoundShaderParameter(Parameter::PROJECTION_MATRIX);
		cameraProjection != nullptr)
	{
		shader->setMat4(cameraProjection, viewpoint->getProjectionMatrix().data());
	}

	if (const char* cameraPosition = getBoundShaderParameter(Parameter::POSITION);
		cameraPosition != nullptr)
	{
		const Vector3& position = viewpoint->getPosition();
		shader->setVec3(cameraPosition, position.x, position.y, position.z);
	}
}

// End of the namespace gltut
}
