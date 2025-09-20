// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

#pragma once

// Includes
#include "./SceneNodeT.h"
#include "engine/renderer/objects/RenderGeometry.h"
#include "engine/scene/nodes/GeometryNode.h"

namespace gltut
{
// Global classes
/// Implementation of the GeometryNode interface
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
