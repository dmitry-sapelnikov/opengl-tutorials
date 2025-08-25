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

	/**
		\brief Creates a box geometry with non-smooth normals

		\param width The width of the box
		\param height The height of the box
		\param depth The depth of the box

		\return The geometry if it was created successfully, nullptr otherwise

		\note The geometry is created with the following vertex format:
		VertexFormat::VERTEX_FORMAT_POS3_NORM3_TEX2

		\note Negative dimensions produce an inverted geometry
	*/
	Geometry* createBox(
		float width,
		float height,
		float depth,
		bool normal,
		bool textureCoordinates,
		bool tangentBitangent) noexcept final;

	/**
		\brief Creates a sphere geometry with smooth normals

		\param radius The radius of the sphere
		\param subdivisions The number of subdivisions for the sphere, must be greater than 0

		\return The geometry if it was created successfully, nullptr otherwise

		\note The geometry is created with the following vertex format:
		VertexFormat::VERTEX_FORMAT_POS3_NORM3_TEX2

		\note Negative radius produces an inverted geometry
	*/
	Geometry* createSphere(float radius, u32 subdivisions) noexcept final;

private:
	/// The device used to create the geometries
	GraphicsDevice& mRenderer;
};

// End of the namespace gltut
}
