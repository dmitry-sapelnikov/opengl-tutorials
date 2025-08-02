#pragma once

// Includes
#include "engine/core/NonCopyable.h"
#include "engine/factory/material/MaterialModel.h"

namespace gltut
{
// Global classes

/// Implementation of the PhongMaterialModel interface
template <typename MaterialModelInterface>
class MaterialModelT : public MaterialModelInterface, public NonCopyable
{
public:
	// Constructor
	explicit MaterialModelT(Material& material) noexcept :
		mMaterial(material)
	{
	}

	// Returns the material associated with this model
	const Material* getMaterial() const noexcept final
	{
		return &mMaterial;
	}

protected:
	// Returns the material associated with this model
	Material& getMaterial() noexcept
	{
		return mMaterial;
	}

private:
	Material& mMaterial;
};

// End of the namespace gltut
}
