#pragma once

// Includes
#include "engine/graphics/GraphicsDevice.h"
#include "engine/renderer/shader/ShaderRendererBinding.h"
#include "engine/renderer/objects/RenderGeometry.h"
#include "engine/renderer/objects/RenderGeometryGroup.h"
#include "engine/renderer/RenderPass.h"

namespace gltut
{
//	Global classes
///	Represents a render pipeline for the scene
class Renderer
{
public:
	/// Virtual destructor
	virtual ~Renderer() noexcept = default;

	/// Returns the device
	virtual GraphicsDevice* getDevice() noexcept = 0;

	/// Creates a shader material binding
	virtual ShaderRendererBinding* createShaderBinding(
		Shader* shader) noexcept = 0;

	/// Removes a shader material binding
	virtual void removeShaderBinding(
		ShaderRendererBinding* binding) noexcept = 0;

	/// Creates a material
	virtual Material* createMaterial() noexcept = 0;

	/// Removes a material
	virtual void removeMaterial(Material* material) noexcept = 0;

	/// Creates a render geometry
	virtual RenderGeometry* createGeometry(
		const Geometry* geometry,
		const Material* material,
		const Matrix4& transform) noexcept = 0;

	/// Creates a render group
	virtual RenderGeometryGroup* createGeometryGroup() noexcept = 0;

	/// Creates a render pass
	virtual RenderPass* createPass(
		const Viewpoint* viewpoint,
		const RenderObject* object,
		Framebuffer* target,
		u32 materialPass,
		const Color* clearColor,
		bool clearDepth,
		const Rectangle2u* viewport,
		bool cullBack = true,
		bool cullFront = false,
		bool enableBlending = false) noexcept = 0;

	/// Creates a depth-sorted render pass
	virtual RenderPass* createDepthSortedPass(
		const Viewpoint* viewpoint,
		const RenderGeometryGroup* group,
		Framebuffer* target,
		u32 materialPass,
		const Color* clearColor,
		bool clearDepth,
		const Rectangle2u* viewport,
		bool cullBack = true,
		bool cullFront = false,
		bool enableBlending = true) noexcept = 0;

	/// Removes a render pass
	virtual void removePass(RenderPass* pass) noexcept = 0;

	/// Removes all render passes
	virtual void removeAllPasses() noexcept = 0;

	/// Sets the priority of the render pass
	virtual void setPassPriority(RenderPass* pass, int32 priority) noexcept = 0;
};

// End of the namespace gltut
}
