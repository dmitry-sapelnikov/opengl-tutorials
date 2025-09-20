#pragma once

// Includes
#include "engine/graphics/geometry/Geometry.h"
#include "engine/math/Matrix4.h"
#include "engine/renderer/objects/RenderGeometry.h"
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
