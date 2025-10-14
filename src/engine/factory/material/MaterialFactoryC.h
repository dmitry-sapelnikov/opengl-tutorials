// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

#pragma once

// Includes
#include "engine/core/NonCopyable.h"
#include "engine/factory/material/MaterialFactory.h"
#include "engine/renderer/Renderer.h"
#include <deque>
#include <map>

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

	/// Creates a Phong material model
	PhongMaterialModel* createPhongMaterial(
		const PhongShaderModel* phongShader,
		bool castShadows = true) noexcept final;

	/// Returns the depth shader
	virtual ShaderRendererBinding* getDepthShader() noexcept final;

	/// Updates the factory
	void update() noexcept final;

private:
	/// Creates the view projection matrix uniform buffer
	void createViewProjectionBuffer();

	/// Creates the flat color shader
	void createFlatColorShader();

	/// Creates the depth shader
	void createDepthShader();

	/// The device
	Renderer& mRenderer;

	/// The scene
	Scene& mScene;

	/// View projection matrix uniform buffer
	ShaderUniformBufferRendererBinding* mViewProjectionBuffer = nullptr;

	/// Flat color shader binding
	ShaderRendererBinding* mFlatColorShader = nullptr;

	/// Depth shader binding
	ShaderRendererBinding* mDepthShader = nullptr;

	/// Flat color material models
	std::deque<FlatColorMaterialModelC> mFlatColorModels;

	/// Pointer to the Phong material shader
	std::deque<PhongShaderModelC> mPhongShaders;

	/// Phong material models
	std::deque<PhongMaterialModelC> mPhongModels;
};

// End of the namespace gltut
}
