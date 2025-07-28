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
	/// Returns the mesh
	virtual Mesh* getMesh() const noexcept = 0;

	/// Adds a mesh
	virtual void setMesh(Mesh* mesh) noexcept = 0;

	/// Returns the material
	virtual Material* getMaterial() const noexcept = 0;

	/// Sets a material
	virtual void setMaterial(Material* material) noexcept = 0;

	/// Renders the object
	virtual void render() const noexcept = 0;
};

// End of the namespace gltut
}
