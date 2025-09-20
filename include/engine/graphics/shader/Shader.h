// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

#pragma once

// Includes
#include "ShaderParameters.h"
#include "engine/core/Check.h"

namespace gltut
{
/// Represents a shader (shader program in OpenGL terminology)
class Shader : public ShaderParameters
{
public:
	/// Virtual destructor
	virtual ~Shader() noexcept = default;

	/// Binds the shader
	virtual void bind() const noexcept = 0;
};

// End of the namespace gltut
}
