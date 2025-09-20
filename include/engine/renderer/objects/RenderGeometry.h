// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

#pragma once

// Includes
#include "engine/graphics/geometry/Geometry.h"
#include "engine/math/Matrix4.h"
#include "engine/renderer/material/Material.h"
#include "engine/renderer/objects/RenderObject.h"

namespace gltut
{
// Global classes
/// Represents a render pipeline for the scene
class RenderGeometry : public RenderObject
{
public:
	virtual const Geometry* getGeometry() const noexcept = 0;

	virtual void setGeometry(const Geometry* geometry) noexcept = 0;

	virtual const Material* getMaterial() const noexcept = 0;

	virtual void setMaterial(const Material* material) noexcept = 0;

	virtual const Matrix4& getTransform() const noexcept = 0;

	virtual void setTransform(const Matrix4& transform) noexcept = 0;
};

// End of the namespace gltut
}
