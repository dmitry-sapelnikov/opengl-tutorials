#pragma once

// Includes
#include "engine/renderer/viewpoint/Viewpoint.h"
#include "engine/renderer/material/Material.h"
#include "engine/factory/shader/PhongShaderModel.h"

namespace gltut
{
// Global classes
class PhongMaterialModel
{
public:
	virtual ~PhongMaterialModel() noexcept = default;

	virtual PhongShaderModel* getPhongShader() const noexcept = 0;

	virtual const Material* getMaterial() const noexcept = 0;

	virtual void setDiffuse(Texture* diffuse) noexcept = 0;

	virtual void setSpecular(Texture* specular) noexcept = 0;

	virtual void setShininess(float shininess) noexcept = 0;
};

// End of the namespace gltut
}
