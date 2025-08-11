#pragma once

// Includes
#include "engine/graphics/geometry/GeometryManager.h"
#include "../../core/ItemManagerT.h"

namespace gltut
{

/// GraphicsDevice base class
class GraphicsDeviceBase;

/// Implementation of the GeometryManager interface
class GeometryManagerC : public ItemManagerT<GeometryManager>
{
public:
	/// Constructor
	GeometryManagerC(GraphicsDeviceBase& device) noexcept :
		mDevice(device)
	{
	}

	/// Creates a geometry
	virtual Geometry* create(
		VertexFormat vertexFormat,
		u32 vertexCount,
		const float* vertices,
		u32 indexCount,
		const u32* indices) noexcept final;

private:
	/// Reference to the graphics device
	GraphicsDeviceBase& mDevice;
};

// End of the namespace gltut
}
