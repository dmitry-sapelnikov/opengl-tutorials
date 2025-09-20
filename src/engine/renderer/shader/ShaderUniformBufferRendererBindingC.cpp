// Includes
#include "ShaderUniformBufferRendererBindingC.h"
#include "engine/renderer/Renderer.h"

namespace gltut
{
// Global classes
void ShaderUniformBufferRendererBindingC::update(
	const Viewpoint* viewpoint,
	float aspectRatio) const noexcept
{
	ShaderUniformBuffer* target = getTarget();

	if (target == nullptr || viewpoint == nullptr)
	{
		return;
	}

	if (const u32* offset = getParameterOffset(RendererBinding::Parameter::VIEWPOINT_VIEW_MATRIX);
		offset != nullptr)
	{
		target->setData(viewpoint->getViewMatrix().data(), sizeof(Matrix4), *offset);
	}

	if (const u32* offset = getParameterOffset(RendererBinding::Parameter::VIEWPOINT_PROJECTION_MATRIX);
		offset != nullptr)
	{
		target->setData(viewpoint->getProjectionMatrix(aspectRatio).data(), sizeof(Matrix4), *offset);
	}

	if (const u32* offset = getParameterOffset(RendererBinding::Parameter::VIEWPOINT_POSITION);
		offset != nullptr)
	{
		const Vector3 position = viewpoint->getPosition();
		target->setData(&position[0], sizeof(Vector3), *offset);
	}
}

void ShaderUniformBufferRendererBindingC::update(const RenderGeometry* geometry) const noexcept
{
	ShaderUniformBuffer* target = getTarget();
	if (target == nullptr || geometry == nullptr)
	{
		return;
	}

	if (const u32* offset = getParameterOffset(RendererBinding::Parameter::GEOMETRY_MATRIX);
		offset != nullptr)
	{
		target->setData(geometry->getTransform().data(), sizeof(Matrix4), *offset);
	}

	if (const u32* offset = getParameterOffset(RendererBinding::Parameter::GEOMETRY_NORMAL_MATRIX);
		offset != nullptr)
	{
		const Matrix3 normalMatrix = getNormalMatrix(geometry->getTransform().getMatrix3());
		target->setData(normalMatrix.data(), sizeof(Matrix3), *offset);
	}
}

// End of the namespace gltut
}
