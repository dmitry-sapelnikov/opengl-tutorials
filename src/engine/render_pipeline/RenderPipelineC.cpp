#pragma once

// Includes
#include "RenderPipelineC.h"
#include <algorithm>
#include "./RenderPassC.h"
#include "./material/ShaderMaterialBindingC.h"
#include "./material/MaterialC.h"
#include "./viewpoint/ShaderViewpointBindingC.h"
#include "./objects/RenderGeometryC.h"
#include "./objects/RenderGroupC.h"

namespace gltut
{

namespace
{
	/// Helper function to create an element in a container
	template <typename InterfaceType, typename ClassType, typename ...Args>
	InterfaceType* createElement(
		std::vector<std::unique_ptr<InterfaceType>>& container,
		const std::string& elementName,
		Args&&... args)
	{
		InterfaceType* result = nullptr;
		GLTUT_CATCH_ALL_BEGIN
			result = container.emplace_back(
				std::make_unique<ClassType>(std::forward<Args>(args)...)).get();
		GLTUT_CATCH_ALL_END("Cannot create an " + elementName)
		return result;
	}
}

//	Global classes
RenderPipelineC::RenderPipelineC(Renderer& renderer) noexcept :
	mRenderer(renderer)
{
}

ShaderViewpointBinding* RenderPipelineC::createShaderViewpointBinding(
	Shader* shader) noexcept
{
	return createElement<ShaderViewpointBinding, ShaderViewpointBindingC>(
		mShaderViewpointBindings,
		"shader viewpoint binding",
		shader);
}

void RenderPipelineC::removeShaderMaterialBinding(
	ShaderMaterialBinding* binding) noexcept
{
	auto it = std::find_if(
		mShaderMaterialBindings.begin(),
		mShaderMaterialBindings.end(),
		[&binding](const auto& currentBinding)
		{
			return currentBinding.get() == binding;
		});
	if (it != mShaderMaterialBindings.end())
	{
		mShaderMaterialBindings.erase(it);
	}
}

ShaderMaterialBinding* RenderPipelineC::createShaderMaterialBinding(
	Shader* shader) noexcept
{
	return createElement<ShaderMaterialBinding, ShaderMaterialBindingC>(
		mShaderMaterialBindings,
		"shader material binding",
		shader);
}

void RenderPipelineC::removeShaderViewpointBinding(
	ShaderViewpointBinding* binding) noexcept
{
	auto it = std::find_if(
		mShaderViewpointBindings.begin(),
		mShaderViewpointBindings.end(),
		[&binding](const auto& currentBinding)
		{
			return currentBinding.get() == binding;
		});
	if (it != mShaderViewpointBindings.end())
	{
		mShaderViewpointBindings.erase(it);
	}
}

Material* RenderPipelineC::createMaterial() noexcept
{
	return createElement<Material, MaterialC>(
		mMaterials,
		"material");
}

void RenderPipelineC::removeMaterial(Material* material) noexcept
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

RenderGeometry* RenderPipelineC::createGeometry(
	const Mesh* geometry,
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

RenderGroup* RenderPipelineC::createGroup() noexcept
{
	return createElement<RenderGroup, RenderGroupC>(
		mGroups,
		"render group");
}

RenderPass* RenderPipelineC::createPass(
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
			mRenderer,
			mShaderViewpointBindings),
			0).first.get();
	GLTUT_CATCH_ALL_END("Cannot create a scene render pass")
	return result;
}

void RenderPipelineC::setPassPriority(RenderPass* pass, int32 priority) noexcept
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

void RenderPipelineC::execute() noexcept
{
	for (const auto& pass : mPasses)
	{
		pass.first->execute();
	}
}

// End of the namespace gltut
}
