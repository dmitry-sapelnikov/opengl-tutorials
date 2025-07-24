#ifndef OPENGL_TUTORIALS_PHONG_MATERIAL_H
#define OPENGL_TUTORIALS_PHONG_MATERIAL_H

// Includes
#include "engine/Renderer.h"
#include "Material.h"

namespace gltut
{

// Global functions
/**
	\brief Creates a Phong shader
	\note The shader assumes the following vertex format:
	- 0: Position (vec3)
	- 1: Normal (vec3)
	- 2: Texture coordinates (vec2)
*/
Shader* createPhongShader(Renderer& renderer) noexcept;

/// Sets the Phong material parameters
void setPhongMaterialParameters(
	Material& material,
	Texture* diffuse = nullptr,
	Texture* ambient = nullptr,
	Texture* specular = nullptr,
	float shininess = 32.0f) noexcept;

// End of the namespace gltut
}

#endif
