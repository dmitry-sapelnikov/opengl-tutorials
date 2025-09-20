#pragma once

// Includes
#include "engine/core/ItemManager.h"
#include "engine/core/Types.h"

#include "engine/math/Color.h"
#include "engine/math/Rectangle.h"

#include "engine/graphics/RenderModes.h"
#include "engine/graphics/framebuffer/FramebufferManager.h"
#include "engine/graphics/geometry/GeometryManager.h"
#include "engine/graphics/shader/ShaderManager.h"
#include "engine/graphics/shader/ShaderUniformBufferManager.h"
#include "engine/graphics/texture/TextureManager.h"

namespace gltut
{
// Global classes
/**
	The graphics device interface for 
	OpenGL/DirectX/Vulkan/Metal/etc. abstraction
*/
class GraphicsDevice
{
public:
	/// Virtual destructor
	virtual ~GraphicsDevice() noexcept = default;

	/// Clears the current render target
	virtual void clear(
		const Color* color,
		bool depth) noexcept = 0;

	/// Returns the geometry manager
	virtual GeometryManager* getGeometries() = 0;

	/// Returns the framebuffer manager
	virtual FramebufferManager* getFramebuffers() = 0;

	/// Return the shader manager
	virtual ShaderManager* getShaders() = 0;

	/// Returns the shader uniform buffer manager
	virtual ShaderUniformBufferManager* getShaderUniformBuffers() = 0;

	/// Returns the texture manager
	virtual TextureManager* getTextures() = 0;

	/// Binds a texture to a slot
	virtual void bindTexture(const Texture* texture, u32 slot) noexcept = 0;

	/// Binds a shader uniform buffer to a binding point
	virtual void bindShaderUniformBuffer(
		const ShaderUniformBuffer* buffer,
		u32 bindingPoint) noexcept = 0;

	/// Binds a framebuffer
	virtual void bindFramebuffer(
		Framebuffer* frameBuffer,
		Rectangle2u* viewport) noexcept = 0;

	/// Enables or disables vertical synchronization
	virtual void enableVSync(bool vSync) noexcept = 0;

	/// Sets the face cull mode
	virtual void setFaceCulling(FaceCullingMode mode) noexcept = 0;

	/// Enable or disables blending
	virtual void setBlending(bool enabled) noexcept = 0;

	/// Sets the depth function
	virtual void setDepthTest(DepthTestMode mode) noexcept = 0;

	/**
		\brief Sets the polygon fill mode

		\param mode The polygon fill mode

		\param size The size of the polygon outline.
		Used only if mode is PolygonFillMode::LINE or PolygonFillMode::POINT

		\param enableSizeInShader If true, the size parameter is passed to the shader.
		Used only if mode is PolygonFillMode::POINT
	*/
	virtual void setPolygonFill(
		PolygonFillMode mode,
		float size = 1.0f,
		bool enableSizeInShader = false) noexcept = 0;
};

// End of the namespace gltut
}
