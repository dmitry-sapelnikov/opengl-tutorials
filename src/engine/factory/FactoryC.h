#pragma once

// Includes
#include "engine/core/NonCopyable.h"
#include "engine/factory/Factory.h"

#include "./geometry/GeometryFactoryC.h"
#include "./material/MaterialFactoryC.h"
#include "./render_pass/RenderPassFactoryC.h"

namespace gltut
{

/// Implementation of the Factory interface
class FactoryC final : public Factory, public NonCopyable
{
public:
	// Constructor
	FactoryC(
		RenderPipeline& renderer,
		Scene& scene) noexcept;

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

private:
	/// The geometry factory
	GeometryFactoryC mGeometry;

	/// The material factory
	MaterialFactoryC mMaterial;

	/// The render pass factory
	RenderPassFactoryC mRenderPass;
};

// End of the namespace gltut
}
