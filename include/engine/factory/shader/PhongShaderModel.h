#pragma once

// Includes
#include "engine/renderer/shader/ShaderRendererBinding.h"

namespace gltut
{
// Global functions
class PhongShaderModel
{
public:
	// The number of texture slots used by the Phong shader
	static constexpr u32 TEXTURE_SLOTS_COUNT = 2;

	// The default shininess value
	static constexpr float DEFAULT_SHINESS = 32.0f;

	/// Virtual destructor
	virtual ~PhongShaderModel() noexcept = default;

	/// Returns the shader renderer binding for the Phong shader
	virtual ShaderRendererBinding* getShader() const noexcept = 0;

	/// Returns the maximum number of directional lights
	virtual u32 getMaxDirectionalLights() const noexcept = 0;

	/// Returns the maximum number of point lights
	virtual u32 getMaxPointLights() const noexcept = 0;

	/// Returns the maximum number of spot lights
	virtual u32 getMaxSpotLights() const noexcept = 0;
};

// End of the namespace gltut
}
