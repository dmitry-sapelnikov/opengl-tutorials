// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

#pragma once

// Includes
#include "engine/renderer/Renderer.h"
#include "engine/scene/Scene.h"

namespace gltut
{
// Global functions
/// Creates a depth-only shader
ShaderRendererBinding* createDepthShader(Renderer& renderer) noexcept;

// End of the namespace gltut
}
