#pragma once

// Includes
#include "engine/math/Matrix4.h"
#include "engine/renderer/mesh/Mesh.h"
#include "engine/render_pipeline/objects/RenderGeometry.h"
#include "engine/scene/nodes/SceneNode.h"

namespace gltut
{
// Global classes
/// The class represents a geometry scene node
class GeometryNode : public SceneNode
{
public:
	/// Returns the render geometry associated with this node
	virtual RenderGeometry* getGeometry() = 0;
};

// End of the namespace gltut
}
