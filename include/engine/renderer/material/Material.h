// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

#pragma once

// Includes
#include "engine/renderer/material/MaterialPass.h"
#include "engine/renderer/shader/ShaderRendererBinding.h"

namespace gltut
{

// Global classes
/// The class represents a multi-pass material
class Material
{
public:
	/// Virtual destructor
	virtual ~Material() noexcept = default;

	/// Creates a material pass by index
	virtual MaterialPass* createPass(
		u32 index,
		const ShaderRendererBinding* shader,
		u32 textureSlotsCount,
		u32 shaderBindingPointsCount) noexcept = 0;

	/// Removes a material pass by index
	virtual void removePass(u32 index) noexcept = 0;

	/// Returns a material pass by index. Returns nullptr if the pass does not exist.
	virtual MaterialPass* getPass(u32 index) const noexcept = 0;

	/// Operator []. Returns a material pass by index.
	MaterialPass* operator[](u32 index) const noexcept
	{
		return getPass(index);
	}
};

// End of the namespace gltut
}
