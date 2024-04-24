#ifndef OPENGL_TUTORIALS_RENDERER_BASE_H
#define OPENGL_TUTORIALS_RENDERER_BASE_H

// Includes
#include "engine/core/NonCopyable.h"
#include "engine/Renderer.h"
#include "engine/EventHandler.h"

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
	virtual void onResize(u32 width, u32 height) noexcept = 0;
};

// End of the namespace gltut
}

#endif
