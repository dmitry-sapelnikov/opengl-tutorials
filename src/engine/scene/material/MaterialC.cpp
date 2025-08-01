// Includes
#include "MaterialC.h"

#include "engine/core/Check.h"
#include "engine/renderer/Renderer.h"
#include "engine/scene/nodes/GeometryNode.h"

namespace gltut
{
//	Global classes
MaterialC::MaterialC(SceneShaderBinding* Shader) noexcept :
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
	return slot < Texture::TEXTURE_SLOTS ? mTextures[slot] : nullptr;
}

void MaterialC::setTexture(Texture* texture, u32 slot) noexcept
{
	if (slot >= Texture::TEXTURE_SLOTS)
	{
		return;
	}

	mTextures[slot] = texture;
	auto findResult = std::find_if(
		mTextures.begin(),
		mTextures.end(),
		[](const Texture* tex) { return tex != nullptr; });

	mBoundTextureSlots = findResult != mTextures.end() ?
		static_cast<u32>(std::distance(mTextures.begin(), findResult)) + 1 :
		0;
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
	for (u32 i = 0; i < mBoundTextureSlots; ++i)
	{
		renderer.bindTexture(mTextures[i], i);
	}
}

// End of the namespace gltut
}
