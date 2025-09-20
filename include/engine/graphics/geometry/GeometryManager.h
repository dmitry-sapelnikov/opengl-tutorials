// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

#pragma once

// Includes
#include "engine/core/ItemManager.h"
#include "engine/graphics/geometry/Geometry.h"

namespace gltut
{
// Global classes
/// Interface for geometry management
class GeometryManager : public ItemManager<Geometry>
{
public:
	/// Creates a geometry
	virtual Geometry* create(
		VertexFormat vertexFormat,
		u32 vertexCount,
		const float* vertices,
		u32 indexCount,
		const u32* indices) noexcept = 0;
};

// End of the namespace gltut
}
