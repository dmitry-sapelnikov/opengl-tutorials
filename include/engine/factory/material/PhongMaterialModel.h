#pragma once

// Includes
#include "engine/render_pipeline/viewpoint/Viewpoint.h"
#include "engine/render_pipeline/material/Material.h"

namespace gltut
{
// Global classes
class PhongMaterialModel
{
public:
	virtual ~PhongMaterialModel() noexcept = default;

	virtual const Material* getMaterial() const noexcept = 0;

	virtual void setDiffuse(Texture* diffuse) noexcept = 0;

	virtual void setSpecular(Texture* specular) noexcept = 0;

	virtual void setShininess(float shininess) noexcept = 0;

	virtual void setDirectinalLightShadow(
		u32 lightIndex,
		const Viewpoint* shadowView,
		const Texture* shadowMap) noexcept = 0;

	/// Updates the model before rendering
	virtual void update() noexcept = 0;
};

// End of the namespace gltut
}
