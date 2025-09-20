// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

#pragma once

// Includes
#include "engine/core/ItemManager.h"
#include "engine/renderer/objects/RenderGeometry.h"

namespace gltut
{
// Global classes
/// Represents a render pipeline for the scene
class RenderGeometryGroup : public RenderObject
{
public:
	/**
		Adds a render geometry to the group
		\note the method does not check cycles in groups
	*/
	virtual void add(RenderGeometry* geometry) noexcept = 0;

	/// Removes a render geometry from the group
	virtual void remove(RenderGeometry* geometry) noexcept = 0;

	/// Removes all geometries from the group
	virtual void clear() noexcept = 0;

	/// Returns the number of geometries in the group
	virtual u32 getSize() const noexcept = 0;

	/// Return the i-th geometry in the group
	virtual RenderGeometry* get(u32 index) const noexcept = 0;
};

// End of the namespace gltut
}
