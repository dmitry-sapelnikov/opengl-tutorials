// Includes
#include "ShaderMaterialBindingC.h"
#include "engine/render_pipeline/objects/RenderGeometry.h"

namespace gltut
{

// Global classes
void ShaderMaterialBindingC::update(const RenderGeometry* geometry) const noexcept
{
	Shader* shader = getShader();
	if (shader == nullptr || geometry == nullptr)
	{
		return;
	}

	shader->bind();

	if (const char* objectMatrix = getBoundShaderParameter(Parameter::GEOMETRY_MATRIX);
		objectMatrix != nullptr)
	{
		shader->setMat4(objectMatrix, geometry->getTransform().data());
	}

	if (const char* objectNormalMatrix = getBoundShaderParameter(Parameter::GEOMETRY_NORMAL_MATRIX);
		objectNormalMatrix != nullptr)
	{
		const Matrix3 normalMatrix = getNormalMatrix(geometry->getTransform().getMatrix3());
		shader->setMat3(objectNormalMatrix, normalMatrix.data());
	}
}

// End of the namespace gltut
}
