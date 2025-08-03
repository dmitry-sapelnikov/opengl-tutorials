// Includes
#include "MaterialC.h"

#include "engine/core/Check.h"
#include "engine/renderer/Renderer.h"
#include "engine/scene/nodes/GeometryNode.h"

namespace gltut
{
//	Global classes
MaterialC::MaterialC(
	SceneShaderBinding* Shader,
	u32 textureSlotsCount) noexcept :

	mShaderBinding(Shader),
	mShaderArguments(Shader != nullptr ? 
		Shader->getShader() :
		nullptr),
	mTextures()
{
	for (u32 i = 0; i < Texture::TEXTURE_SLOTS; ++i)
	{
		mTextures[i] = nullptr;
	}
	setTextureSlotsCount(textureSlotsCount);
}

/// Returns the shader binding
const SceneShaderBinding* MaterialC::getShader() const noexcept
{
	return mShaderBinding;
}

void MaterialC::setShader(const SceneShaderBinding* shader) noexcept
{
	mShaderBinding = shader;
	mShaderArguments.setShader(shader != nullptr ?
		shader->getShader() :
		nullptr);
}

Texture* MaterialC::getTexture(u32 slot) const noexcept
{
	return slot < mTextureSlotsCount ? mTextures[slot] : nullptr;
}

void MaterialC::setTexture(Texture* texture, u32 slot) noexcept
{
	if (slot < mTextureSlotsCount)
	{
		mTextures[slot] = texture;
	}
}

void MaterialC::activate(const GeometryNode* node) const noexcept
{
	if (node == nullptr ||
		mShaderBinding == nullptr || 
		mShaderBinding->getShader() == nullptr ||
		mShaderBinding->getShader()->getRenderer() == nullptr)
	{
		return;
	}

	mShaderBinding->activate(node);
	mShaderArguments.activate();
	
	Renderer& renderer = *mShaderBinding->getShader()->getRenderer();
	for (u32 i = 0; i < mTextureSlotsCount; ++i)
	{
		renderer.bindTexture(mTextures[i], i);
	}
}

// End of the namespace gltut
}
