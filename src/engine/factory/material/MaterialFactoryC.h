#pragma once

// Includes
#include <deque>
#include "engine/core/NonCopyable.h"
#include "engine/renderer/Renderer.h"
#include "engine/scene/Scene.h"
#include "engine/factory/material/MaterialFactory.h"
#include "./phong/PhongMaterialModelC.h"

namespace gltut
{
/// Implementation of the GeometryFactory class
class MaterialFactoryC final : public MaterialFactory, public NonCopyable
{
public:
	// Constructor
	explicit MaterialFactoryC(Renderer& renderer, Scene& scene) noexcept;

	///	Creates a Phong material model
	PhongMaterialModel* createPhongModel() noexcept final;

private:
	/// The renderer used to create shaders
	Renderer& mRenderer;

	/// The scene used to create materials
	Scene& mScene;

	/// Pointer to the Phong material shader
	SceneShaderBinding* mPhongShader = nullptr;

	/// Phong material models
	std::deque<PhongMaterialModelC> mPhongModels;
};

// End of the namespace gltut
}
