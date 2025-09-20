// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

#pragma once

// Includes
#include <array>

#include "engine/core/NonCopyable.h"
#include "engine/scene/texture/SceneTextureSetBinding.h"

namespace gltut
{
// Global classes
/// Implementation of the SceneTextureSetBinding interface
class SceneTextureSetBindingC final : public SceneTextureSetBinding, public NonCopyable
{
public:
	/// Constructor
	SceneTextureSetBindingC(TextureSet* textureSet) noexcept :
		mTextureSet(textureSet)
	{
		mParameters.fill(std::numeric_limits<u32>::max());
	}

	/// Returns the bound texture set
	TextureSet* getTextureSet() const noexcept final
	{
		return mTextureSet;
	}

	/// Sets the bound texture set
	void setTextureSet(
		TextureSet* textureSet,
		bool resetParameters = false) noexcept final
	{
		mTextureSet = textureSet;
		if (resetParameters)
		{
			for (auto& parameter : mParameters)
			{
				parameter = std::numeric_limits<u32>::max();
			}
		}
	}

	/**
		Binds a scene parameter to texture slots
		\param parameter The scene parameter to bind
		\param startSlot The starting texture slot to bind the textures
	*/
	void bind(
		Parameter parameter,
		u32 startSlot) noexcept final
	{
		const size_t index = static_cast<size_t>(parameter);
		if (index >= TOTAL_PARAMETERS)
		{
			return;
		}
		mParameters[index] = startSlot;
	}

	void unbind(Parameter parameter) noexcept final
	{
		if (const size_t index = static_cast<size_t>(parameter);
			index < TOTAL_PARAMETERS)
		{
			mParameters[index] = std::numeric_limits<u32>::max();
		}
	}

	/// Returns the start texture slot for a scene parameter, nullptr if not bound
	const u32* getStartTextureSlot(Parameter parameter) const noexcept final
	{
		const size_t index = static_cast<size_t>(parameter);
		if (index >= TOTAL_PARAMETERS)
		{
			return nullptr;
		}
		const u32& result = mParameters[index];
		return result == std::numeric_limits<u32>::max() ? nullptr : &result;
	}

	/// Updates the binding for a scene
	void update(const Scene* scene) const noexcept final;

private:
	/// The bound texture set
	TextureSet* mTextureSet = nullptr;

	/// The shader parameters for the scene parameters
	std::array<u32, TOTAL_PARAMETERS> mParameters;
};

// End of the namespace gltut
}
