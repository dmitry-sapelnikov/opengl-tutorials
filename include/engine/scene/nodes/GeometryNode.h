#pragma once

// Includes
#include "engine/math/Matrix4.h"
#include "engine/renderer/mesh/Mesh.h"
#include "engine/scene/material/Material.h"
#include "engine/scene/nodes/SceneNode.h"

namespace gltut
{
// Global classes
/// The class represents a geometry scene node
class GeometryNode : public SceneNode
{
public:
	/// Adds a mesh
	virtual void setMesh(const Mesh* mesh) noexcept = 0;

	/// Sets a material
	virtual void setMaterial(const Material* material) noexcept = 0;

	/// Renders the object
	virtual void render() const noexcept = 0;
};

// End of the namespace gltut
}
