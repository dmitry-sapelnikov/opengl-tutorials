// Includes
#include "MaterialPassC.h"

#include "engine/core/Check.h"
#include "engine/graphics/GraphicsDevice.h"
#include "engine/scene/nodes/GeometryNode.h"

namespace gltut
{
//	Global classes
MaterialPassC::MaterialPassC(
	ShaderMaterialBinding* Shader,
	u32 textureSlotsCount) noexcept :

	mShaderBinding(Shader),
	mShaderArguments(Shader != nullptr ? 
		Shader->getShader() :
		nullptr),
	mTextures(textureSlotsCount)
{
}

/// Returns the shader binding
const ShaderMaterialBinding* MaterialPassC::getShader() const noexcept
{
	return mShaderBinding;
}

void MaterialPassC::setShader(const ShaderMaterialBinding* shader) noexcept
{
	mShaderBinding = shader;
	mShaderArguments.setShader(shader != nullptr ?
		shader->getShader() :
		nullptr);
}

void MaterialPassC::bind(const RenderGeometry* geometry) const noexcept
{
	if (geometry == nullptr ||
		mShaderBinding == nullptr || 
		mShaderBinding->getShader() == nullptr)
	{
		return;
	}

	mShaderBinding->update(geometry);
	mShaderArguments.bind();
	mTextures.bind();
}

// End of the namespace gltut
}
