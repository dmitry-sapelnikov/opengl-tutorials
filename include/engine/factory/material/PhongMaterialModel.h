#pragma once

// Includes
#include "engine/scene/material/Material.h"

namespace gltut
{
// Global classes
class PhongMaterialModel
{
public:
	virtual const Material* getMaterial() const noexcept = 0;

	virtual void setDiffuse(Texture* diffuse) noexcept = 0;

	virtual void setSpecular(Texture* specular) noexcept = 0;

	virtual void setShininess(float shininess) noexcept = 0;
};

// End of the namespace gltut
}
