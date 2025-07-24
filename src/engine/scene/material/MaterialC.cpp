// Includes
#include "MaterialC.h"
#include "engine/core/Check.h"

namespace gltut
{
//	Global classes
MaterialC::MaterialC(Shader* shader) noexcept :
	mShaderArguments(shader),
	mTextures()
{
	for (u32 i = 0; i < TEXTURE_SLOTS; ++i)
	{
		mTextures[i] = nullptr;
	}
}

Shader* MaterialC::getShader() const noexcept
{
	return mShaderArguments.getShader();
}

void MaterialC::setShader(Shader* shader) noexcept
{
	mShaderArguments.setShader(shader);
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

void MaterialC::activate() const noexcept
{
	if (mShaderArguments.getShader() != nullptr)
	{
		mShaderArguments.activate();
	}
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
