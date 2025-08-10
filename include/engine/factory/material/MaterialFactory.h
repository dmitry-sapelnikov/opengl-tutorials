#pragma once

// Includes
#include "engine/graphics/GraphicsDevice.h"
#include "engine/scene/Scene.h"
#include "engine/factory/material/FlatColorMaterialModel.h"
#include "engine/factory/material/PhongShaderModel.h"
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
	virtual PhongShaderModel* createPhongShader(
		u32 maxDirectionalLights,
		u32 maxPointLights,
		u32 maxSpotLights) noexcept = 0;

	///	Creates a Phong material model
	virtual PhongMaterialModel* createPhongMaterial(
		PhongShaderModel* phongShader) noexcept = 0;

	/// Updates the material factory
	virtual void update() noexcept = 0;
};

// End of the namespace gltut
}
