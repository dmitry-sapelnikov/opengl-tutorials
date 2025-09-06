#pragma once

// Includes
#include "engine/core/NonCopyable.h"
#include "engine/renderer/Renderer.h"

namespace gltut
{
// Global classes

/// Implementation of the PhongMaterialModel interface
template <typename MaterialModelInterface>
class MaterialModelT : public MaterialModelInterface, public NonCopyable
{
public:
	// Constructor
	explicit MaterialModelT(Renderer& renderer) :
		mRenderer(renderer),
		mMaterial(renderer.createMaterial())
	{
		GLTUT_CHECK(mMaterial != nullptr, "Failed to create a material");
	}

	// Virtual destructor
	virtual ~MaterialModelT() noexcept
	{
		mRenderer.removeMaterial(mMaterial);
	}

	// Returns the material associated with this model
	Material* getMaterial() const noexcept final
	{
		return mMaterial;
	}

protected:
	Material& getMaterial() noexcept
	{
		GLTUT_ASSERT(mMaterial != nullptr);
		return *mMaterial;
	}

private:
	/// The renderer
	Renderer& mRenderer;

	/// The material
	Material* mMaterial;
};

// End of the namespace gltut
}
