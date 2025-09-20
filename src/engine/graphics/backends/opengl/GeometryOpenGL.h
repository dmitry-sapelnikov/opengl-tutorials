#pragma once

// Includes
#include "engine/core/NonCopyable.h"
#include "engine/graphics/geometry/Geometry.h"

namespace gltut
{
// Global classes
/// OpenGL implementation of a geometry
class GeometryOpenGL final : public Geometry, public NonCopyable
{
public:
	/// Constructor
	GeometryOpenGL(
		VertexFormat vertexFormat,
		u32 vertexCount,
		const float* vertices,
		u32 indexCount,
		const u32* indices);

	/// Destructor
	~GeometryOpenGL() final;

	/// Renders the geometry
	void render() const noexcept final;

private:
	/// Indices count
	u32 mIndexCount;

	/// The vertex buffer object
	u32 mVertexBuffer = 0;

	/// The element buffer object
	u32 mIndexBuffer = 0;

	/// The vertex array object
	u32 mVertexArray = 0;
};

// End of the namespace gltut
}
