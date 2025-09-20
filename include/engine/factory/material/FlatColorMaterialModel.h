// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

#pragma once

// Includes
#include "engine/renderer/material/Material.h"

namespace gltut
{
// Global classes
class FlatColorMaterialModel
{
public:
	/// Virtual destructor
	virtual ~FlatColorMaterialModel() = default;

	/// Returns the underlying material
	virtual Material* getMaterial() const noexcept = 0;

	/// Sets the color texture
	virtual void setColor(const Texture* color) noexcept = 0;

	/// Sets the transparency threshold
	virtual void setTransparencyThreshold(float threshold) noexcept = 0;
};

// End of the namespace gltut
}
