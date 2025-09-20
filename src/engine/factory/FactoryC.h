// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

#pragma once

// Includes
#include "engine/core/NonCopyable.h"
#include "engine/factory/Factory.h"

#include "./geometry/GeometryFactoryC.h"
#include "./material/MaterialFactoryC.h"
#include "./render_pass/RenderPassFactoryC.h"
#include "./scene/SceneFactoryC.h"
#include "./texture/TextureFactoryC.h"

namespace gltut
{
// Global classes
/// Implementation of the Factory interface
class FactoryC final : public Factory, public NonCopyable
{
public:
	// Constructor
	FactoryC(
		Renderer& renderer,
		Scene& scene,
		Window& window) noexcept;

	/// Returns the geometry factory
	GeometryFactory* getGeometry() noexcept final
	{
		return &mGeometry;
	}

	/// Returns the material factory
	MaterialFactory* getMaterial() noexcept final
	{
		return &mMaterial;
	}

	/// Returns the render pass factory
	RenderPassFactory* getRenderPass() noexcept final
	{
		return &mRenderPass;
	}

	/// Returns the texture factory
	TextureFactory* getTexture() noexcept final
	{
		return &mTexture;
	}

	/// Returns the shadow factory
	SceneFactory* getScene() noexcept final
	{
		return &mScene;
	}

	/// Updates the factory
	void update() noexcept final
	{
		mMaterial.update();
		mScene.update();
	}

private:
	/// The geometry factory
	GeometryFactoryC mGeometry;

	/// The material factory
	MaterialFactoryC mMaterial;

	/// The render pass factory
	RenderPassFactoryC mRenderPass;

	/// The texture factory
	TextureFactoryC mTexture;

	/// The scene factory
	SceneFactoryC mScene;
};

// End of the namespace gltut
}
