#ifndef OPENGL_TUTORIALS_PHONG_MATERIAL_H
#define OPENGL_TUTORIALS_PHONG_MATERIAL_H

// Includes
#include "engine/renderer/Renderer.h"
#include "engine/scene/Scene.h"

namespace gltut
{
// Global functions
/// Creates a Phong shader
SceneShaderBinding* createPhongShader(Renderer& renderer, Scene& scene) noexcept;

// End of the namespace gltut
}

#endif
