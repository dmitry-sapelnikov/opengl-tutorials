#pragma once

// Includes
#include "engine/graphics/GraphicsDevice.h"
#include "engine/renderer/viewpoint/ShaderViewpointBinding.h"
#include "engine/renderer/objects/RenderGeometry.h"
#include "engine/renderer/objects/RenderGroup.h"
#include "engine/renderer/RenderPass.h"

namespace gltut
{
//	Global classes
///	Represents a render pipeline for the scene
class RenderPipeline
{
public:
	/// Virtual destructor
	virtual ~RenderPipeline() noexcept = default;

	/// Returns the device
	virtual GraphicsDevice* getDevice() noexcept = 0;

	/// Creates a shader material binding
	virtual ShaderMaterialBinding* createShaderMaterialBinding(
		Shader* shader) noexcept = 0;

	/// Removes a shader material binding
	virtual void removeShaderMaterialBinding(
		ShaderMaterialBinding* binding) noexcept = 0;

	/// Creates a shader viewpoint binding
	virtual ShaderViewpointBinding* createShaderViewpointBinding(
		Shader* shader) noexcept = 0;

	/// Removes a shader viewpoint binding
	virtual void removeShaderViewpointBinding(
		ShaderViewpointBinding* binding) noexcept = 0;

	/// Creates a material
	virtual Material* createMaterial() noexcept = 0;

	/// Removes a material
	virtual void removeMaterial(Material* material) noexcept = 0;

	/// Creates a render geometry
	virtual RenderGeometry* createGeometry(
		const Mesh* geometry,
		const Material* material,
		const Matrix4& transform) noexcept = 0;

	/// Creates a render group
	virtual RenderGroup* createGroup() noexcept = 0;

	/// Creates a render pass
	virtual RenderPass* createPass(
		const Viewpoint* viewpoint,
		const RenderObject* object,
		Framebuffer* target,
		u32 materialPass,
		const Color* clearColor,
		bool clearDepth,
		const Rectangle2u* viewport) noexcept = 0;

	/// Removes a render pass
	virtual void removePass(RenderPass* pass) noexcept = 0;

	/// Sets the priority of the render pass
	virtual void setPassPriority(RenderPass* pass, int32 priority) noexcept = 0;
};

// End of the namespace gltut
}
