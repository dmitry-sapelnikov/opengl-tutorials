#pragma once

// Includes
#include "engine/core/NonCopyable.h"
#include "engine/renderer/Renderer.h"
#include "engine/scene/Scene.h"
#include "engine/factory/material/PhongShaderModel.h"

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
	ShaderMaterialBinding* getMaterialBinding() const noexcept final
	{
		return mMaterialBinding;
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

private:
	/// The maximum number of directional lights
	u32 mMaxDirectionalLights;

	/// The maximum number of point lights
	u32 mMaxPointLights;

	/// The maximum number of spot lights
	u32 mMaxSpotLights;

	/// The renderer
	Renderer& mRenderer;

	/// The scene
	Scene& mScene;

	/// The shader
	Shader* mShader = nullptr;

	/// The viewpoint binding
	ShaderViewpointBinding* mViewpointBinding = nullptr;

	/// The material binding
	ShaderMaterialBinding* mMaterialBinding = nullptr;

	/// The scene binding
	SceneShaderBinding* mSceneBinding = nullptr;
};

// End of the namespace gltut
}
