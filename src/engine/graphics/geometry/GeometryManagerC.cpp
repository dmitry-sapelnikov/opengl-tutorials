// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

// Includes
#include "GeometryManagerC.h"
#include <string>
#include "../GraphicsDeviceBase.h"

namespace gltut
{

// Global classes
Geometry* GeometryManagerC::create(
	VertexFormat vertexFormat,
	u32 vertexCount,
	const float* vertices,
	u32 indexCount,
	const u32* indices) noexcept
{
	Geometry* result = nullptr;
	GLTUT_CATCH_ALL_BEGIN
		result = add(mDevice.createBackendGeometry(
			vertexFormat,
			vertexCount,
			vertices,
			indexCount,
			indices));
	GLTUT_CATCH_ALL_END("Failed to create geometry")
	return result;
}

// End of the namespace gltut
}
