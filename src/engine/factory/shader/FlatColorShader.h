#pragma once

// Includes
#include "engine/renderer/Renderer.h"
#include "engine/scene/Scene.h"

namespace gltut
{
// Global functions
/// Creates a flat color shader
ShaderRendererBinding* createFlatColorShader(Renderer& renderer) noexcept;

// End of the namespace gltut
}

