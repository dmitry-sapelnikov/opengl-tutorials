// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

#pragma once

// Includes
#include "engine/core/ItemManager.h"
#include "engine/graphics/shader/Shader.h"

namespace gltut
{

// Global classes
/// Interface for Shader management
class ShaderManager : public ItemManager<Shader>
{
public:
	/// Creates a shader from strings
	virtual Shader* create(
		const char* vertexShader,
		const char* fragmentShader) noexcept = 0;

	/// Creates a shader from files
	virtual Shader* load(
		const char* vertexShaderPath,
		const char* fragmentShaderPath) noexcept = 0;
};

// End of the namespace gltut
}
