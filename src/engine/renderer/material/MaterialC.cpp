// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

// Includes
#include "MaterialC.h"
#include "./MaterialPassC.h"

namespace gltut
{
// Global classes
MaterialPass* MaterialC::createPass(
	u32 index,
	const ShaderRendererBinding* shader,
	u32 textureSlotsCount,
	u32 shaderBindingPointsCount) noexcept
{
	if (index < mPasses.size() && mPasses[index] != nullptr)
	{
		return mPasses[index].get();
	}

	MaterialPass* result = nullptr;
	GLTUT_CATCH_ALL_BEGIN
		auto pass = std::make_unique<MaterialPassC>(
			mDevice,
			shader,
			textureSlotsCount,
			shaderBindingPointsCount);

		if (index >= mPasses.size())
		{
			mPasses.resize(index + 1);
		}
		mPasses[index] = std::move(pass);
		result = mPasses[index].get();
	GLTUT_CATCH_ALL_END("Cannot create a material pass")
	return result;
}

void MaterialC::removePass(u32 index) noexcept
{
	GLTUT_ASSERT(index < mPasses.size());
	if (index < mPasses.size())
	{
		mPasses[index].reset();
	}
}

MaterialPass* MaterialC::getPass(u32 index) const noexcept
{
	return index < mPasses.size() ? mPasses[index].get() : nullptr;
}

// End of the namespace gltut
}
