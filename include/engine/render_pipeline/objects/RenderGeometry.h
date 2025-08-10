#pragma once

// Includes
#include "engine/math/Matrix4.h"
#include "engine/graphics/mesh/Mesh.h"
#include "engine/render_pipeline/objects/RenderObject.h"
#include "engine/render_pipeline/material/Material.h"

namespace gltut
{
//	Global classes
///	Represents a render pipeline for the scene
class RenderGeometry : public RenderObject
{
public:
	virtual const Mesh* getGeometry() const noexcept = 0;

	virtual void setGeometry(const Mesh* geometry) noexcept = 0;

	virtual const Material* getMaterial() const noexcept = 0;

	virtual void setMaterial(const Material* material) noexcept = 0;

	virtual const Matrix4& getTransform() const noexcept = 0;

	virtual void setTransform(const Matrix4& transform) noexcept = 0;
};

// End of the namespace gltut
}
