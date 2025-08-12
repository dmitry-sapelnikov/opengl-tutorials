#pragma once

// Includes
#include <deque>
#include <map>
#include "engine/core/NonCopyable.h"
#include "engine/renderer/Renderer.h"
#include "engine/factory/material/MaterialFactory.h"

#include "../shader/PhongShaderModelC.h"
#include "./FlatColorMaterialModelC.h"
#include "./PhongMaterialModelC.h"

namespace gltut
{
/// Implementation of the GeometryFactory class
class MaterialFactoryC final : public MaterialFactory, public NonCopyable
{
public:
	/// Constructor
	explicit MaterialFactoryC(
		Renderer& renderer,
		Scene& scene) noexcept;

	/// Destructor
	~MaterialFactoryC() noexcept final;

	/// Creates a flat color material model
	FlatColorMaterialModel* createFlatColorMaterial(
		bool castShadows = true) noexcept final;

	/// Creates a Phong shader
	PhongShaderModel* createPhongShader(
		u32 maxDirectionalLights,
		u32 maxPointLights,
		u32 maxSpotLights) noexcept final;

	///	Creates a Phong material model
	PhongMaterialModel* createPhongMaterial(
		PhongShaderModel* phongShader,
		bool castShadows = true) noexcept final;

	/// Updates the factory
	void update() noexcept final;

private:
	/// Creates the flat color shader
	void createFlatColorShader();

	/// Creates the depth shader
	void createDepthShader();

	/// The device
	Renderer& mRenderer;

	/// The scene
	Scene& mScene;

	/// Flat color shader binding
	ShaderRendererBinding* mFlatColorShader = nullptr;

	/// Depth shader binding
	ShaderRendererBinding* mDepthShader = nullptr;

	/// Flat color material models
	std::deque<FlatColorMaterialModelC> mFlatColorModels;

	/// Pointer to the Phong material shader
	std::map<std::tuple<u32, u32, u32>, PhongShaderModelC> mPhongShaders;

	/// Phong material models
	std::deque<PhongMaterialModelC> mPhongModels;
};

// End of the namespace gltut
}
