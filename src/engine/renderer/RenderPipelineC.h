#pragma once

// Includes
#include <vector>
#include <memory>

#include "engine/core/NonCopyable.h"
#include "engine/renderer/RenderPipeline.h"
#include "engine/graphics/GraphicsDevice.h"
#include "engine/scene/Scene.h"

namespace gltut
{
//	Global classes
///	Represents a render pipeline for the scene
class RenderPipelineC final : public RenderPipeline, public NonCopyable
{
public:
	/// Constructor
	explicit RenderPipelineC(GraphicsDevice& device) noexcept;

	/// Returns the device
	GraphicsDevice* getDevice() noexcept
	{
		return &mDevice;
	}

	/// Creates a shader material binding
	ShaderMaterialBinding* createShaderMaterialBinding(
		Shader* shader) noexcept final;

	/// Removes a shader material binding
	void removeShaderMaterialBinding(
		ShaderMaterialBinding* binding) noexcept final;


	/// Creates a shader viewpoint binding
	ShaderViewpointBinding* createShaderViewpointBinding(
		Shader* shader) noexcept final;

	/// Removes a shader viewpoint binding
	void removeShaderViewpointBinding(
		ShaderViewpointBinding* binding) noexcept final;

	/// Creates a material
	Material* createMaterial() noexcept final;

	/// Removes a material
	void removeMaterial(Material* material) noexcept final;

	/// Creates a render geometry
	RenderGeometry* createGeometry(
		const Mesh* geometry,
		const Material* material,
		const Matrix4& transform) noexcept final;

	/// Creates a render group
	RenderGroup* createGroup() noexcept final;

	/// Creates a render pass
	RenderPass* createPass(
		const Viewpoint* viewpoint,
		const RenderObject* object,
		Framebuffer* target,
		u32 materialPass,
		const Color* clearColor,
		bool clearDepth,
		const Rectangle2u* viewport) noexcept final;

	/// Removes a render pass
	void removePass(RenderPass* pass) noexcept final;

	/// Sets the priority of the render pass
	void setPassPriority(RenderPass* pass, int32 priority) noexcept final;

	/// Executes the render pipeline
	void execute() noexcept;

private:
	/// GraphicsDevice
	GraphicsDevice& mDevice;

	/// Shader viewpoint bindings
	std::vector<std::unique_ptr<ShaderViewpointBinding>> mShaderViewpointBindings;

	/// Shader material bindings
	std::vector<std::unique_ptr<ShaderMaterialBinding>> mShaderMaterialBindings;

	/// Materials
	std::vector<std::unique_ptr<Material>> mMaterials;

	/// Geometries
	std::vector<std::unique_ptr<RenderGeometry>> mGeometries;

	/// Groups
	std::vector<std::unique_ptr<RenderGroup>> mGroups;

	/// List of render passes
	std::vector<std::pair<std::unique_ptr<RenderPass>, u32>> mPasses;
};

// End of the namespace gltut
}
