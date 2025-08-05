#pragma once

// Includes
#include "engine/scene/nodes/GeometryNode.h"
#include "engine/render_pipeline/objects/RenderGeometry.h"
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

	/// Sets the transform
	void setTransform(const Matrix4& transform) noexcept final
	{
		SceneNodeT<GeometryNode>::setTransform(transform);
		mGeometry.setTransform(getGlobalTransform());
	}

private:
	/// The geometry
	RenderGeometry& mGeometry;
};

// End of the namespace gltut
}
