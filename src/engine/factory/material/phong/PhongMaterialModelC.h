#pragma once

// Includes
#include <string>
#include <unordered_map>
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
		getMaterial()[0]->setTexture(diffuse, 0);
	}

	// Sets the specular texture
	void setSpecular(Texture* specular) noexcept final
	{
		getMaterial()[0]->setTexture(specular, 1);
	}

	// Sets the shininess value
	void setShininess(float shininess) noexcept final
	{
		getMaterial()[0]->getShaderArguments()->setFloat("shininess", shininess);
	}

	void setDirectinalLightShadow(
		u32 lightIndex,
		const Viewpoint* shadowView,
		const Texture* shadowMap) noexcept final;
	
	/// Updates the material
	void update() noexcept final;

private:
	std::unordered_map<u32, const Viewpoint*> mDirectionalLightShadows;
};

// End of the namespace gltut
}
