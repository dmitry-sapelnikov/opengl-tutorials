#ifndef OPENGL_TUTORIALS_RENDERER_BASE_H
#define OPENGL_TUTORIALS_RENDERER_BASE_H

// Includes
#include <unordered_map>
#include "engine/core/NonCopyable.h"
#include "engine/renderer/Renderer.h"
#include "engine/renderer/Mesh.h"
#include "engine/window/EventHandler.h"

namespace gltut
{

/// Renderer base class
class RendererBase : public Renderer, public EventHandler, public NonCopyable
{
public:
	/// Invalid mesh index
	static constexpr u32 INVALID_MESH_INDEX = std::numeric_limits<u32>::max();

	/// Loads a texture
	Texture* loadTexture(const char* path) noexcept final;

	/// Creates a solid color texture
	Texture* createSolidColorTexture(
		float r,
		float g,
		float b,
		float a = 1.0f) noexcept final;

	/// Adds a mesh
	virtual u32 addMesh(const Mesh& mesh) noexcept = 0;

	/// Removes a mesh
	virtual void removeMesh(u32 index) noexcept = 0;

	/// Renders a mesh
	virtual void renderMesh(u32 index) const noexcept = 0;
	
	/// Called when an event occurs
	void onEvent(const Event& event) noexcept final;

private:
	/// Called when the window is resized
	virtual void onResize(const Point2u& size) noexcept = 0;

	/// Solid color textures
	std::unordered_map<u32, Texture*> mSolidColorTextures;
};

// End of the namespace gltut
}

#endif
