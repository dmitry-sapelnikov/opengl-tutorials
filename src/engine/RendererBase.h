#ifndef OPENGL_TUTORIALS_RENDERER_BASE_H
#define OPENGL_TUTORIALS_RENDERER_BASE_H

// Includes
#include "engine/core/NonCopyable.h"
#include "engine/Renderer.h"

namespace gltut
{

/// Renderer base class
class RendererBase : public Renderer, public NonCopyable
{
public:
	/// Loads a texture
	Texture* loadTexture(const char* path) noexcept final;
};

// End of the namespace gltut
}

#endif
