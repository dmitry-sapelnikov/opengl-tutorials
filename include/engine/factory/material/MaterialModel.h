// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

#pragma once

// Includes
#include "engine/renderer/material/Material.h"

namespace gltut
{
// Global classes

/**
	\brief The material model interface.
	Provides access to the underlying material.
*/
class MaterialModel
{
public:
	/// Virtual destructor
	virtual ~MaterialModel() noexcept = default;

	/// Returns the material associated with this model
	virtual const Material* getMaterial() const noexcept = 0;
};

// End of the namespace gltut
}
