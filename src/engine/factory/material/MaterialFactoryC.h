#pragma once

// Includes
#include <deque>
#include <map>
#include "engine/core/NonCopyable.h"
#include "engine/render_pipeline/RenderPipeline.h"
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
	explicit MaterialFactoryC(
		RenderPipeline& renderer,
		Scene& scene) noexcept;

	/// Creates a flat color material model
	FlatColorMaterialModel* createFlatColorMaterial() noexcept final;

	/// Creates a Phong shader
	ShaderMaterialBinding* createPhongShader(
		u32 maxDirectionalLights,
		u32 maxPointLights,
		u32 maxSpotLights) noexcept final;

	///	Creates a Phong material model
	PhongMaterialModel* createPhongMaterial(
		ShaderMaterialBinding* phongShader) noexcept final;

private:
	/// The renderer
	RenderPipeline& mRenderer;

	/// The scene
	Scene& mScene;

	/// Flat color shader binding
	ShaderMaterialBinding* mFlatColorShader = nullptr;

	/// Flat color material models
	std::deque<FlatColorMaterialModelC> mFlatColorModels;

	/// Pointer to the Phong material shader
	std::map<std::tuple<u32, u32, u32>, ShaderMaterialBinding*> mPhongShaders;

	/// Phong material models
	std::deque<PhongMaterialModelC> mPhongModels;
};

// End of the namespace gltut
}
