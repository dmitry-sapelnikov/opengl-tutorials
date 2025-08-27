#pragma once

// Includes
#include "engine/core/NonCopyable.h"
#include "engine/graphics/GraphicsDevice.h"
#include "engine/factory/geometry/GeometryFactory.h"

namespace gltut
{

/// Implementation of the GeometryFactory class
class GeometryFactoryC final : public GeometryFactory, public NonCopyable
{
public:
	// Constructor
	explicit GeometryFactoryC(GraphicsDevice& device) noexcept :
		mRenderer(device)
	{
	}

	Geometry* createQuad(
		const Vector2& size,
		const CreationOptions& options) noexcept final;

	Geometry* createBox(
		const Vector3& size,
		const CreationOptions& options) noexcept final;

	Geometry* createSphere(float radius, u32 subdivisions) noexcept final;

private:
	Geometry* createGeometry(
		const Vector3* positions,
		const Vector3* normals,
		const Vector2* textureCoordinates,
		u32 vertexCount,
		const u32* indices,
		u32 indexCount,
		const CreationOptions& options) noexcept;

	/// The device used to create the geometries
	GraphicsDevice& mRenderer;
};

// End of the namespace gltut
}
