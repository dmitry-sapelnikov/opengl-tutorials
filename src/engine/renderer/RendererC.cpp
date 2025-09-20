// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

#pragma once

// Includes
#include "RendererC.h"

#include <algorithm>

#include "./material/MaterialC.h"
#include "./objects/RenderGeometryC.h"
#include "./objects/RenderGeometryGroupC.h"
#include "./render_pass/DepthSortedRenderPassC.h"
#include "./render_pass/RenderPassC.h"
#include "./shader/ShaderRendererBindingC.h"
#include "./shader/ShaderUniformBufferRendererBindingC.h"

namespace gltut
{

namespace
{
// Local functions
/// Helper function to create an element in a container
template <typename InterfaceType, typename ClassType, typename... Args>
InterfaceType* createElement(
	std::vector<std::unique_ptr<InterfaceType>>& container,
	const std::string& elementName,
	Args&&... args)
{
	InterfaceType* result = nullptr;
	GLTUT_CATCH_ALL_BEGIN
	result = container.emplace_back(
						  std::make_unique<ClassType>(std::forward<Args>(args)...))
				 .get();
	GLTUT_CATCH_ALL_END("Cannot create an " + elementName)
	return result;
}
}

// Global classes
RendererC::RendererC(GraphicsDevice& device) noexcept :
	mDevice(device)
{
}

ShaderRendererBinding* RendererC::createShaderBinding(
	Shader* shader) noexcept
{
	return createElement<ShaderRendererBinding, ShaderRendererBindingC>(
		mShaderBindings,
		"shader material binding",
		shader);
}

void RendererC::removeShaderBinding(
	ShaderRendererBinding* binding) noexcept
{
	auto it = std::find_if(
		mShaderBindings.begin(),
		mShaderBindings.end(),
		[&binding](const auto& currentBinding)
		{
			return currentBinding.get() == binding;
		});
	if (it != mShaderBindings.end())
	{
		mShaderBindings.erase(it);
	}
}

ShaderUniformBufferRendererBinding* RendererC::createShaderUniformBufferBinding(
	ShaderUniformBuffer* buffer) noexcept
{
	return createElement<ShaderUniformBufferRendererBinding, ShaderUniformBufferRendererBindingC>(
		mShaderUniformBufferBindings,
		"shader uniform buffer binding",
		buffer);
}

void RendererC::removeShaderUniformBufferBinding(
	ShaderUniformBufferRendererBinding* binding) noexcept
{
	auto it = std::find_if(
		mShaderUniformBufferBindings.begin(),
		mShaderUniformBufferBindings.end(),
		[&binding](const auto& currentBinding)
		{
			return currentBinding.get() == binding;
		});
	if (it != mShaderUniformBufferBindings.end())
	{
		mShaderUniformBufferBindings.erase(it);
	}
}

Material* RendererC::createMaterial() noexcept
{
	return createElement<Material, MaterialC>(
		mMaterials,
		"material",
		mDevice);
}

void RendererC::removeMaterial(Material* material) noexcept
{
	auto it = std::find_if(
		mMaterials.begin(),
		mMaterials.end(),
		[&material](const auto& currentMaterial)
		{
			return currentMaterial.get() == material;
		});
	if (it != mMaterials.end())
	{
		mMaterials.erase(it);
	}
}

RenderGeometry* RendererC::createGeometry(
	const Geometry* geometry,
	const Material* material,
	const Matrix4& transform) noexcept
{
	return createElement<RenderGeometry, RenderGeometryC>(
		mGeometries,
		"render geometry",
		geometry,
		material,
		transform);
}

RenderGeometryGroup* RendererC::createGeometryGroup() noexcept
{
	return createElement<RenderGeometryGroup, RenderGeometryGroupC>(
		mGroups,
		"render group");
}

RenderPass* RendererC::createPass(
	const Viewpoint* viewpoint,
	const RenderObject* object,
	Framebuffer* target,
	u32 materialPass,
	const Color* clearColor,
	bool clearDepth,
	const Rectangle2u* viewport) noexcept
{
	RenderPass* result = nullptr;
	GLTUT_CATCH_ALL_BEGIN
	result = mPasses.emplace_back(std::make_unique<RenderPassC>(
									  viewpoint,
									  object,
									  target,
									  materialPass,
									  clearColor,
									  clearDepth,
									  viewport,
									  mDevice,
									  mShaderBindings,
									  mShaderUniformBufferBindings),
								  0)
				 .first.get();
	GLTUT_CATCH_ALL_END("Cannot create a scene render pass")

	setPassPriority(result, 0);
	return result;
}

void RendererC::removeAllPasses() noexcept
{
	mPasses.clear();
}

RenderPass* RendererC::createDepthSortedPass(
	const Viewpoint* viewpoint,
	const RenderGeometryGroup* group,
	Framebuffer* target,
	u32 materialPass,
	const Color* clearColor,
	bool clearDepth,
	const Rectangle2u* viewport) noexcept
{
	RenderPass* result = nullptr;
	GLTUT_CATCH_ALL_BEGIN
	result = mPasses.emplace_back(std::make_unique<DepthSortedRenderPassC>(
		viewpoint,
		group,
		target,
		materialPass,
		clearColor,
		clearDepth,
		viewport,
		mDevice,
		mShaderBindings,
		mShaderUniformBufferBindings),
		0).first.get();
	GLTUT_CATCH_ALL_END("Cannot create a depth-sorted scene render pass")

	setPassPriority(result, 0);
	return result;
}

void RendererC::removePass(RenderPass* pass) noexcept
{
	auto findResult = std::find_if(
		mPasses.begin(),
		mPasses.end(),
		[&pass](const auto& currentPass)
		{
			return currentPass.first.get() == pass;
		});

	if (findResult != mPasses.end())
	{
		mPasses.erase(findResult);
	}
}

void RendererC::setPassPriority(RenderPass* pass, int32 priority) noexcept
{
	auto findResult = std::find_if(
		mPasses.begin(),
		mPasses.end(),
		[&pass](const auto& currentPass)
		{
			return currentPass.first.get() == pass;
		});

	if (findResult != mPasses.end())
	{
		findResult->second = priority;
		std::sort(
			mPasses.begin(),
			mPasses.end(),
			[](const auto& pass1, const auto& pass2)
			{
				return pass1.second < pass2.second;
			});
	}
}

void RendererC::execute() noexcept
{
	for (const auto& pass : mPasses)
	{
		if (pass.first->isActive())
		{
			pass.first->execute();
		}
	}
}

// End of the namespace gltut
}
