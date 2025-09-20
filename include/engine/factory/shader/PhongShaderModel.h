#pragma once

// Includes
#include "engine/renderer/shader/ShaderRendererBinding.h"

namespace gltut
{
// Global classes
/**
	The Phong shader model interface. Provides access to the underlying shader
	and its properties.
*/
class PhongShaderModel
{
public:
	// The number of texture slots used by the Phong shader
	static constexpr u32 TEXTURE_SLOTS_COUNT = 4;

	// The default shininess value
	static constexpr float DEFAULT_SHINESS = 32.0f;

	/// The default min bias
	static constexpr float DEFAULT_MIN_SHADOW_MAP_BIAS = 0.0005f;

	/// The default max bias
	static constexpr float DEFAULT_MAX_SHADOW_MAP_BIAS = 0.005f;

	/// The binding point for the view-projection matrix uniform buffer
	static constexpr u32 VIEW_PROJECTION_BUFFER_BINDING_POINT = 0;

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

	/// Returns the minimum bias for the shadow map
	virtual float getMinShadowMapBias() const noexcept = 0;

	/// Sets the minimum bias for the shadow map.
	/// Clamps the bias to [0, max bias].
	virtual void setMinShadowMapBias(float bias) noexcept = 0;

	/// Returns the maximum bias for the shadow map
	virtual float getMaxShadowMapBias() const noexcept = 0;

	/// Sets the maximum bias for the shadow map.
	/// Clamps the bias to non-negative, min bias to [0, max bias].
	virtual void setMaxShadowMapBias(float bias) noexcept = 0;
};

// End of the namespace gltut
}
