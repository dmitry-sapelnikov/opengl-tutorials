// Includes
#include "MaterialC.h"
#include "engine/core/Check.h"

namespace gltut
{
//	Global classes
MaterialC::MaterialC(Shader* shader) noexcept :
	mShader(shader)
{
	for (u32 i = 0; i < TEXTURE_SLOTS; ++i)
	{
		mTextures[i] = nullptr;
	}
}

Shader* MaterialC::getShader() const noexcept
{
	return mShader;
}

void MaterialC::setShader(Shader* shader) noexcept
{
	mShader = shader;
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

void MaterialC::use() noexcept
{
	if (mShader != nullptr)
	{
		mShader->use();
	}

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
