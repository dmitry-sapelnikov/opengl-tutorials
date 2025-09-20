// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

#pragma once

// Includes
#include "../../core/ItemManagerT.h"
#include "engine/graphics/Shader/ShaderManager.h"

namespace gltut
{
// Global classes
// Forward declarations
class GraphicsDeviceBase;

/// Implementation of the ShaderManager interface
class ShaderManagerC : public ItemManagerT<ShaderManager>
{
public:
	/// Constructor
	ShaderManagerC(GraphicsDeviceBase& device) noexcept :
		mDevice(device)
	{
	}

	/// Creates a shader from strings
	Shader* create(
		const char* vertexShader,
		const char* fragmentShader) noexcept final;

	/// Creates a shader from files
	Shader* load(
		const char* vertexShaderPath,
		const char* fragmentShaderPath) noexcept final;

private:
	/// Reference to the graphics device
	GraphicsDeviceBase& mDevice;
};

// End of the namespace gltut
}
