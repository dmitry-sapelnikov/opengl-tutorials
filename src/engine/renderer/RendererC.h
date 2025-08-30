#pragma once

// Includes
#include <vector>
#include <memory>

#include "engine/core/NonCopyable.h"
#include "engine/renderer/Renderer.h"
#include "engine/graphics/GraphicsDevice.h"
#include "engine/scene/Scene.h"

namespace gltut
{
//	Global classes
///	Represents a render pipeline for the scene
class RendererC final : public Renderer, public NonCopyable
{
public:
	/// Constructor
	explicit RendererC(GraphicsDevice& device) noexcept;

	/// Returns the device
	GraphicsDevice* getDevice() noexcept
	{
		return &mDevice;
	}

	/// Creates a shader material binding
	ShaderRendererBinding* createShaderBinding(
		Shader* shader) noexcept final;

	/// Removes a shader material binding
	void removeShaderBinding(
		ShaderRendererBinding* binding) noexcept final;

	/// Creates a material
	Material* createMaterial() noexcept final;

	/// Removes a material
	void removeMaterial(Material* material) noexcept final;

	/// Creates a render geometry
	RenderGeometry* createGeometry(
		const Geometry* geometry,
		const Material* material,
		const Matrix4& transform) noexcept final;

	/// Creates a render geometry group
	RenderGeometryGroup* createGeometryGroup() noexcept final;

	/// Creates a render pass
	RenderPass* createPass(
		const Viewpoint* viewpoint,
		const RenderObject* object,
		Framebuffer* target,
		u32 materialPass,
		const Color* clearColor,
		bool clearDepth,
		const Rectangle2u* viewport,
		bool cullBackFaces = true,
		bool cullFrontFaces = false) noexcept final;

	RenderPass* createDepthSortedPass(
		const Viewpoint* viewpoint,
		const RenderGeometryGroup* group,
		Framebuffer* target,
		u32 materialPass,
		const Color* clearColor,
		bool clearDepth,
		const Rectangle2u* viewport,
		bool cullBackFaces = true,
		bool cullFrontFaces = false) noexcept final;

	/// Removes a render pass
	void removePass(RenderPass* pass) noexcept final;

	/// Sets the priority of the render pass
	void setPassPriority(RenderPass* pass, int32 priority) noexcept final;

	/// Executes the render pipeline
	void execute() noexcept;

private:
	/// GraphicsDevice
	GraphicsDevice& mDevice;

	/// Shader renderer bindings
	std::vector<std::unique_ptr<ShaderRendererBinding>> mShaderBindings;

	/// Materials
	std::vector<std::unique_ptr<Material>> mMaterials;

	/// Geometries
	std::vector<std::unique_ptr<RenderGeometry>> mGeometries;

	/// Groups
	std::vector<std::unique_ptr<RenderGeometryGroup>> mGroups;

	/// List of render passes
	std::vector<std::pair<std::unique_ptr<RenderPass>, u32>> mPasses;
};

// End of the namespace gltut
}
