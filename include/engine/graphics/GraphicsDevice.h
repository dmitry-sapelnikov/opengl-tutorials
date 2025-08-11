#pragma once

// Includes
#include "engine/core/Types.h"
#include "engine/core/ItemManager.h"
#include "engine/math/Color.h"
#include "engine/math/Rectangle.h"
#include "engine/graphics/geometry/Geometry.h"
#include "engine/graphics/shader/Shader.h"
#include "engine/graphics/texture/TextureManager.h"
#include "engine/graphics/framebuffer/TextureFramebuffer.h"

namespace gltut
{
//	Global classes
///	The graphics device
class GraphicsDevice
{
public:
	/// Virtual destructor
	virtual ~GraphicsDevice() noexcept = default;

	/// Clears the current render target
	virtual void clear(
		const Color* color,
		bool depth) noexcept = 0;

	/// Creates a geometry
	virtual Geometry* createGeometry(
		VertexFormat vertexFormat,
		u32 vertexCount,
		const float* vertices,
		u32 indexCount,
		const u32* indices) noexcept = 0;

	/// Removes a geometry
	virtual void removeGeometry(Geometry* geometry) noexcept = 0;

	/// Creates a shader from strings
	virtual Shader* createShader(
		const char* vertexShader,
		const char* fragmentShader) noexcept = 0;

	/// Creates a shader from files
	virtual Shader* loadShader(
		const char* vertexShaderPath,
		const char* fragmentShaderPath) noexcept = 0;

	/// Removes a shader
	virtual void removeShader(Shader* shader) noexcept = 0;

	/// Returns the texture manager
	virtual TextureManager* getTextures() = 0;

	/// Binds a texture to a slot
	virtual void bindTexture(const Texture* texture, u32 slot) noexcept = 0;

	/**
		\brief Creates a framebuffer
		\note At least one of texture parameters must be non-null
	*/
	virtual TextureFramebuffer* createTextureFramebuffer(
		Texture* color,
		Texture* depth) noexcept = 0;

	/// Removes a framebuffer
	virtual void removeTextureFramebuffer(TextureFramebuffer* frameBuffer) noexcept = 0;

	/// Returns the window framebuffer
	virtual Framebuffer* getWindowFramebuffer() const noexcept = 0;

	/// Binds a framebuffer
	virtual void bindFramebuffer(
		Framebuffer* frameBuffer,
		Rectangle2u* viewport) noexcept = 0;

	/// Enables or disables vertical synchronization
	virtual void enableVSync(bool vSync) noexcept = 0;

	/// Creates a solid color texture
	virtual const Texture* createSolidColorTexture(
		float r,
		float g,
		float b,
		float a = 1.0f) noexcept = 0;
};

// End of the namespace gltut
}
