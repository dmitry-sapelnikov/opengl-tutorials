// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

#pragma once

// Includes
#include "engine/graphics/shader/ShaderUniformBuffer.h"

namespace gltut
{

// Global classes

/// Represents a set of shader uniform buffers
class ShaderUniformBufferSet
{
public:
	/// Virtual destructor
	virtual ~ShaderUniformBufferSet() noexcept = default;

	/// Returns the uniform buffer at the given binding point, or nullptr if none is set
	virtual const ShaderUniformBuffer* get(u32 bindingPoint) const noexcept = 0;

	/// Sets a uniform buffer at the given binding point
	virtual void set(const ShaderUniformBuffer* uniformBuffer, u32 bindingPoint) noexcept = 0;

	/// Returns the number of binding points
	virtual u32 getBindingPointsCount() const noexcept = 0;

	/// Sets the number of binding points
	virtual void setBindingPointsCount(u32 count) noexcept = 0;

	/// Binds the uniform buffers
	virtual void bind() const noexcept = 0;
};

// End of the namespace gltut
}
