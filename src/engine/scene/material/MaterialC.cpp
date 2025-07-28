// Includes
#include "MaterialC.h"

#include "engine/core/Check.h"
#include "engine/scene/SceneObject.h"

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
	for (u32 i = 0; i < TEXTURE_SLOTS; ++i)
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
	GLTUT_ASSERT(slot < TEXTURE_SLOTS);
	return mTextures[slot];
}

void MaterialC::setTexture(Texture* texture, u32 slot) noexcept
{
	GLTUT_ASSERT(slot < TEXTURE_SLOTS);
	mTextures[slot] = texture;
}

void MaterialC::activate(const SceneObject* object) const noexcept
{
	if (object == nullptr || 
		mShaderBinding == nullptr || 
		mShaderBinding->getShader() == nullptr)
	{
		return;
	}

	mShaderBinding->activate(object);
	mShaderArguments.activate();
	bindTextures();
}

void MaterialC::bindTextures() const noexcept
{
	for (u32 i = 0; i < TEXTURE_SLOTS; ++i)
	{
		if (mTextures[i] != nullptr)
		{
			mTextures[i]->bind(i);
		}
	}
}

// End of the namespace gltut
}
