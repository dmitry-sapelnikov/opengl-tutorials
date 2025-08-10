#pragma once

// Includes
#include "engine/renderer/Renderer.h"
#include "engine/scene/Scene.h"

namespace gltut
{
// Global functions
/// Creates a flat color shader
ShaderMaterialBinding* createFlatColorShader(Renderer& renderPipeline) noexcept;

// End of the namespace gltut
}

