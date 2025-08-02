#pragma once

// Includes
#include "engine/factory/material/PhongMaterialModel.h"
#include "../MaterialModelT.h"

namespace gltut
{
// Global classes

/// Implementation of the PhongMaterialModel interface
class PhongMaterialModelC final : public MaterialModelT<PhongMaterialModel>
{
public:
	/// Constructor
	using MaterialModelT<PhongMaterialModel>::MaterialModelT;

	// Sets the diffuse texture
	void setDiffuse(Texture* diffuse) noexcept final
	{
		getMaterial().setTexture(diffuse, 0);
	}

	// Sets the specular texture
	void setSpecular(Texture* specular) noexcept final
	{
		getMaterial().setTexture(specular, 1);
	}

	// Sets the shininess value
	void setShininess(float shininess) noexcept final
	{
		getMaterial().getShaderArguments()->setFloat("shininess", shininess);
	}
};

// End of the namespace gltut
}
