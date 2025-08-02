#pragma once

// Includes
#include "engine/renderer/Renderer.h"
#include "engine/scene/Scene.h"
#include "engine/factory/material/FlatColorMaterialModel.h"
#include "engine/factory/material/PhongMaterialModel.h"

namespace gltut
{
// Global classes
/// The material factory interface. Creates various scene materials.
class MaterialFactory
{
public:
	/// Virtual destructor
	virtual ~MaterialFactory() noexcept = default;

	/// Creates a flat color material model
	virtual FlatColorMaterialModel* createFlatColorMaterial() noexcept = 0;

	/// Creates a Phong shader
	virtual SceneShaderBinding* createPhongShader(
		Renderer* renderer,
		Scene* scene,
		u32 maxDirectionalLights,
		u32 maxPointLights,
		u32 maxSpotLights) noexcept = 0;

	///	Creates a Phong material model
	virtual PhongMaterialModel* createPhongMaterial(SceneShaderBinding* phongShader) noexcept = 0;
};

// End of the namespace gltut
}
