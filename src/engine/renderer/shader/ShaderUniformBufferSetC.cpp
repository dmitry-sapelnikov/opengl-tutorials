// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

// Includes
#include "ShaderUniformBufferSetC.h"

namespace gltut
{

// Global classes
ShaderUniformBufferSetC::ShaderUniformBufferSetC(
	GraphicsDevice& device,
	u32 bindingPointsCount) :
	mDevice(device),
	mBindingPoints(bindingPointsCount, nullptr)
{
}

const ShaderUniformBuffer* ShaderUniformBufferSetC::get(u32 bindingPoint) const noexcept
{
	if (!GLTUT_ASSERT(bindingPoint < mBindingPoints.size()))
	{
		return nullptr;
	}
	return mBindingPoints[bindingPoint];
}

void ShaderUniformBufferSetC::set(
	const ShaderUniformBuffer* uniformBuffer,
	u32 bindingPoint) noexcept
{
	if (GLTUT_ASSERT(bindingPoint < mBindingPoints.size()))
	{
		mBindingPoints[bindingPoint] = uniformBuffer;
	}
}

u32 ShaderUniformBufferSetC::getBindingPointsCount() const noexcept
{
	return static_cast<u32>(mBindingPoints.size());
}

void ShaderUniformBufferSetC::setBindingPointsCount(u32 count) noexcept
{
	mBindingPoints.resize(count, nullptr);
}

void ShaderUniformBufferSetC::bind() const noexcept
{
	for (u32 i = 0; i < mBindingPoints.size(); ++i)
	{
		mDevice.bindShaderUniformBuffer(mBindingPoints[i], i);
	}
}

// End of the namespace gltut
}
