#pragma once

// Includes
#include <deque>
#include <map>
#include "engine/core/NonCopyable.h"
#include "engine/renderer/Renderer.h"
#include "engine/scene/Scene.h"
#include "engine/factory/material/MaterialFactory.h"

#include "./flat_color/FlatColorMaterialModelC.h"
#include "./phong/PhongMaterialModelC.h"

namespace gltut
{
/// Implementation of the GeometryFactory class
class MaterialFactoryC final : public MaterialFactory, public NonCopyable
{
public:
	// Constructor
	explicit MaterialFactoryC(Renderer& renderer, Scene& scene) noexcept;

	/// Creates a flat color material model
	FlatColorMaterialModel* createFlatColorMaterial() noexcept final;

	/// Creates a Phong shader
	SceneShaderBinding* createPhongShader(
		Renderer* renderer,
		Scene* scene,
		u32 maxDirectionalLights,
		u32 maxPointLights,
		u32 maxSpotLights) noexcept final;

	///	Creates a Phong material model
	PhongMaterialModel* createPhongMaterial(SceneShaderBinding* phongShader) noexcept final;

private:
	/// The renderer used to create shaders
	Renderer& mRenderer;

	/// The scene used to create materials
	Scene& mScene;

	/// Flat color shader binding
	SceneShaderBinding* mFlatColorShader = nullptr;

	/// Flat color material models
	std::deque<FlatColorMaterialModelC> mFlatColorModels;

	/// Pointer to the Phong material shader
	std::map<std::tuple<u32, u32, u32>, SceneShaderBinding*> mPhongShaders;

	/// Phong material models
	std::deque<PhongMaterialModelC> mPhongModels;
};

// End of the namespace gltut
}
