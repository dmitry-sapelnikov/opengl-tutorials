#pragma once

// Includes
#include "engine/scene/nodes/GeometryNode.h"
#include "engine/renderer/objects/RenderGeometry.h"
#include "./SceneNodeT.h"

namespace gltut
{
// Global classes
/// Implementation of the Scene interface
class GeometryNodeC final : public SceneNodeT<GeometryNode>
{
public:
	GeometryNodeC(
		RenderGeometry& geometry,
		const Matrix4& transform,
		SceneNode* parent) noexcept :

		SceneNodeT<GeometryNode>(transform, parent),
		mGeometry(geometry)
	{
		GeometryNodeC::setTransform(transform);
	}

	/// Returns the geometry
	RenderGeometry* getGeometry() noexcept final
	{
		return &mGeometry;
	}

private:
	/// Updates the global transform
	void updateGlobalTransform() noexcept final
	{
		SceneNodeT<GeometryNode>::updateGlobalTransform();
		mGeometry.setTransform(getGlobalTransform());
	}

	/// The geometry
	RenderGeometry& mGeometry;
};

// End of the namespace gltut
}
