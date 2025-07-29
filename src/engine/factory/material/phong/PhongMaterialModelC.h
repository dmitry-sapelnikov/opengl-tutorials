#pragma once

// Includes
#include "engine/core/NonCopyable.h"
#include "engine/factory/material/phong/PhongMaterialModel.h"
#include "engine/scene/material/Material.h"

namespace gltut
{

class PhongMaterialModelC final : public PhongMaterialModel, public NonCopyable
{
public:
	// Constructor
	explicit PhongMaterialModelC(Material& material) noexcept;

	// Returns the material
	const Material* getMaterial() const noexcept final;

	// Sets the ambient texture
	void setAmbient(Texture* ambient) noexcept final;

	// Sets the diffuse texture
	void setDiffuse(Texture* diffuse) noexcept final;

	// Sets the specular texture
	void setSpecular(Texture* specular) noexcept final;

	// Sets the shininess value
	void setShininess(float shininess) noexcept final;

private:
	Material& mMaterial;
};

// End of the namespace gltut
}
