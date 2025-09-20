// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

// Includes
#include "MaterialPassC.h"

#include "engine/core/Check.h"
#include "engine/graphics/GraphicsDevice.h"
#include "engine/scene/nodes/GeometryNode.h"

namespace gltut
{
// Global classes
MaterialPassC::MaterialPassC(
	GraphicsDevice& device,
	const ShaderRendererBinding* shader,
	u32 textureSlotsCount,
	u32 shaderBindingPointsCount) noexcept :

	mDevice(device),
	mShaderBinding(shader),
	mShaderArguments(shader != nullptr ? shader->getTarget() : nullptr),
	mTextures(device, textureSlotsCount),
	mShaderUniformBuffers(device, shaderBindingPointsCount)
{
}

/// Returns the shader binding
const ShaderRendererBinding* MaterialPassC::getShader() const noexcept
{
	return mShaderBinding;
}

void MaterialPassC::setShader(const ShaderRendererBinding* shader) noexcept
{
	mShaderBinding = shader;
	mShaderArguments.setShader(shader != nullptr ? shader->getTarget() : nullptr);
}

void MaterialPassC::bind(const RenderGeometry* geometry) const noexcept
{
	if (geometry == nullptr ||
		mShaderBinding == nullptr ||
		mShaderBinding->getTarget() == nullptr)
	{
		return;
	}

	mShaderBinding->update(geometry);
	mShaderArguments.bind();
	mTextures.bind();
	mShaderUniformBuffers.bind();

	mDevice.setBlending(isTransparent());
	mDevice.setFaceCulling(getFaceCulling());
	mDevice.setPolygonFill(
		mPolygonFill,
		mPolygonFillSize,
		mPolygonFillSizeInShader);
}

// End of the namespace gltut
}
