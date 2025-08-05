#pragma once

// Includes
#include "engine/render_pipeline/material/Material.h"

namespace gltut
{
// Global classes
class MaterialModel
{
public:
	/// Virtual destructor
	virtual ~MaterialModel() noexcept = default;

	/// Returns the material associated with this model
	virtual const Material* getMaterial() const noexcept = 0;
};

// End of the namespace gltut
}
