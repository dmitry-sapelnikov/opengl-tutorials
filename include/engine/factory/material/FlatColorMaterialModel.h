#pragma once

// Includes
#include "engine/render_pipeline/material/Material.h"

namespace gltut
{
// Global classes
class FlatColorMaterialModel
{
public:
	virtual const Material* getMaterial() const noexcept = 0;

	virtual void setColor(Texture* color) noexcept = 0;
};

// End of the namespace gltut
}
