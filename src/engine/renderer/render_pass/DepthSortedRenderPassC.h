// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

#pragma once

// Includes
#include "../objects/RenderGeometryGroupC.h"
#include "RenderPassC.h"

namespace gltut
{
// Global classes
/// Implementation of a depth-sorted render pass
class DepthSortedRenderPassC final : public RenderPassC
{
public:
	/// Constructor
	DepthSortedRenderPassC(
		const Viewpoint* viewpoint,
		const RenderGeometryGroup* group,
		Framebuffer* target,
		u32 materialPass,
		const Color* clearColor,
		bool clearDepth,
		const Rectangle2u* viewport,
		GraphicsDevice& device,
		const ShaderBindings& shaderBindings,
		const ShaderUniformBufferBindings& shaderUniformBufferBindings) noexcept;

	/// Executes the render pass
	void execute() noexcept final;

private:
	/// The group to render
	const RenderGeometryGroup* mGroup;

	/// The depth-sorted group
	RenderGeometryGroupC mSortedGroup;

	/// The view matrix
	Matrix4 mViewMatrix;
};

// End of the namespace gltut
}
