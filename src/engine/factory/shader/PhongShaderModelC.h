#pragma once

// Includes
#include "engine/core/NonCopyable.h"
#include "engine/renderer/Renderer.h"
#include "engine/scene/Scene.h"
#include "engine/factory/shader/PhongShaderModel.h"

namespace gltut
{
// Global functions
class PhongShaderModelC final : public PhongShaderModel, public NonCopyable
{
public:
	/// Constructor
	PhongShaderModelC(
		Renderer& renderer,
		Scene& scene,
		u32 maxDirectionalLights,
		u32 maxPointLights,
		u32 maxSpotLights);

	/// Virtual destructor
	~PhongShaderModelC() noexcept final;

	/// Returns the material binding
	ShaderRendererBinding* getShader() const noexcept final
	{
		return mRendererShaderBinding;
	}

	/// Returns the maximum number of directional lights
	u32 getMaxDirectionalLights() const noexcept final
	{
		return mMaxDirectionalLights;
	}

	/// Returns the maximum number of point lights
	u32 getMaxPointLights() const noexcept final
	{
		return mMaxPointLights;
	}

	/// Returns the maximum number of spot lights
	u32 getMaxSpotLights() const noexcept final
	{
		return mMaxSpotLights;
	}

	/// Returns the minimum bias for the shadow map
	float getMinShadowMapBias() const noexcept final
	{
		return mMinShadowMapBias;
	}

	/// Sets the minimum bias for the shadow map.
	/// Clamps the bias to [0, max bias].
	void setMinShadowMapBias(float bias) noexcept final;

	/// Returns the maximum bias for the shadow map
	float getMaxShadowMapBias() const noexcept final
	{
		return mMaxShadowMapBias;
	}

	/// Sets the maximum bias for the shadow map.
	/// Clamps the bias to non-negative, min bias to [0, max bias].
	void setMaxShadowMapBias(float bias) noexcept final;

private:
	/// The maximum number of directional lights
	u32 mMaxDirectionalLights;

	/// The maximum number of point lights
	u32 mMaxPointLights;

	/// The maximum number of spot lights
	u32 mMaxSpotLights;

	/// The minimum bias for the shadow map
	float mMinShadowMapBias = DEFAULT_MIN_SHADOW_MAP_BIAS;

	/// The maximum bias for the shadow map
	float mMaxShadowMapBias = DEFAULT_MAX_SHADOW_MAP_BIAS;

	/// The renderer
	Renderer& mRenderer;

	/// The scene
	Scene& mScene;

	/// Renderer shader binding
	ShaderRendererBinding* mRendererShaderBinding = nullptr;

	/// The scene binding
	SceneShaderBinding* mSceneBinding = nullptr;
};

// End of the namespace gltut
}
