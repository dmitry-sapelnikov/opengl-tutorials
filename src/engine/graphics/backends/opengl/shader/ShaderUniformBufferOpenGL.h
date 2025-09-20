// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

#pragma once

// Includes
#include "engine/graphics/shader/ShaderUniformBuffer.h"

namespace gltut
{

// Global classes
/// OpenGL implementation of the ShaderUniformBuffer interface
class ShaderUniformBufferOpenGL final : public ShaderUniformBuffer
{
public:
	/**
		Constructor
		\throw std::runtime_error If the shader could not be created
	*/
	ShaderUniformBufferOpenGL(u32 sizeInBytes);

	/// Virtual destructor
	~ShaderUniformBufferOpenGL() noexcept final;

	/// Returns the id of the uniform buffer
	u32 getId() const noexcept final
	{
		return static_cast<u32>(mId);
	}

	/// Sets the data of the uniform buffer
	void setData(const void* data, u32 size, u32 offset) noexcept final;

private:
	/// Binds the uniform buffer
	void bind() const noexcept;

	/// Size of the uniform buffer in bytes
	u32 mSizeInBytes;

	/// ShaderUniformBuffer id
	unsigned mId;
};

// End of the namespace gltut
}
