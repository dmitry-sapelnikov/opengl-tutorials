// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

#pragma once

// Includes
#include "engine/factory/shader/PhongShaderModel.h"
#include "engine/renderer/material/Material.h"
#include "engine/renderer/viewpoint/Viewpoint.h"

namespace gltut
{
// Global classes
/**
	@brief Interface for Phong material models in the gltut engine.
	Provides methods to access and modify material properties
	for use with Phong shading.
*/
class PhongMaterialModel
{
public:
	/// Virtual destructor for safe polymorphic use.
	virtual ~PhongMaterialModel() noexcept = default;

	/// Returns the associated Phong shader model.
	virtual const PhongShaderModel* getPhongShader() const noexcept = 0;

	/// Returns the underlying material.
	virtual const Material* getMaterial() const noexcept = 0;

	/// Sets the diffuse texture.
	virtual void setDiffuse(const Texture* diffuse) noexcept = 0;

	/// Sets the specular texture.
	virtual void setSpecular(const Texture* specular) noexcept = 0;

	/// Sets the normal texture.
	virtual void setNormal(const Texture* normal) noexcept = 0;

	/// Sets the depth (height) texture.
	virtual void setDepth(const Texture* height) noexcept = 0;

	/// Sets the scale for the depth texture.
	virtual void setDepthScale(float depthScale) noexcept = 0;

	/// Sets the shininess factor for specular highlights.
	virtual void setShininess(float shininess) noexcept = 0;
};

// End of the namespace gltut
}
