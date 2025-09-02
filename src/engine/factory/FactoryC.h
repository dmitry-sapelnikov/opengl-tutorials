#pragma once

// Includes
#include "engine/core/NonCopyable.h"
#include "engine/factory/Factory.h"

#include "./geometry/GeometryFactoryC.h"
#include "./material/MaterialFactoryC.h"
#include "./render_pass/RenderPassFactoryC.h"
#include "./shadow/ShadowFactoryC.h"
#include "./texture/TextureFactoryC.h"

namespace gltut
{

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

	/// Returns the shadow factory
	ShadowFactory* getShadow() noexcept final
	{
		return &mShadow;
	}

	/// Returns the texture factory
	TextureFactory* getTexture() noexcept final
	{
		return &mTexture;
	}

	/// Updates the factory
	void update() noexcept final
	{
		mShadow.update();
		mMaterial.update();
	}

private:
	/// The geometry factory
	GeometryFactoryC mGeometry;

	/// The material factory
	MaterialFactoryC mMaterial;

	/// The render pass factory
	RenderPassFactoryC mRenderPass;

	/// The shadow factory
	ShadowFactoryC mShadow;

	/// The texture factory
	TextureFactoryC mTexture;
};

// End of the namespace gltut
}
