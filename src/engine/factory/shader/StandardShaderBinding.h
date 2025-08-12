#pragma once

// Includes
#include "engine/renderer/Renderer.h"

namespace gltut
{
// Global functions
/// Creates a shader binding for a shader with 'model', 'view' and 'projection' uniforms
ShaderRendererBinding* createStandardShaderBinding(
	Renderer& renderer,
	const char* vertexShader,
	const char* fragmentShader) noexcept;

// End of the namespace gltut
}

