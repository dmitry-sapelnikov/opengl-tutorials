// Includes
#include "MaterialPassC.h"

#include "engine/core/Check.h"
#include "engine/graphics/GraphicsDevice.h"
#include "engine/scene/nodes/GeometryNode.h"

namespace gltut
{
//	Global classes
MaterialPassC::MaterialPassC(
	GraphicsDevice& device,
	const ShaderRendererBinding* shader,
	u32 textureSlotsCount) noexcept :

	mDevice(device),
	mShaderBinding(shader),
	mShaderArguments(shader != nullptr ? 
		shader->getShader() :
		nullptr),
	mTextures(device, textureSlotsCount)
{
}

/// Returns the shader binding
const ShaderRendererBinding* MaterialPassC::getShader() const noexcept
{
	return mShaderBinding;
}

void MaterialPassC::setShader(const ShaderRendererBinding* shader) noexcept
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
	
	mDevice.setBlending(isTransparent());
	mDevice.setFaceCulling(getFaceCulling());
	mDevice.setPolygonFill(
		mPolygonFill,
		mPolygonFillSize,
		mPolygonFillSizeInShader);
}

// End of the namespace gltut
}
